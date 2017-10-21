#include <cppcms/application.h>
#include <cppcms/applications_pool.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
#include <cppcms/http_file.h>
#include <cppcms/http_context.h>
#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
#include <cppcms/url_dispatcher.h>
#include <cppcms/url_mapper.h>
#include <fstream>
#include <sstream>
#include "content.h"
#include "tinydir.h"
#include "../vizq-cppcms/codebase/mvq.h"
#include "../vizq-cppcms/codebase/rtree/rtree.h"

#define SOME_PAIR(x,y) make_pair(string(x), vector<string>(y))


using namespace std;
// an application, we may need to create similar classes for other apps
class hello: public cppcms::application {
    bool upload_success;
    string upload_type;
public:
    hello(cppcms::service &srv): cppcms::application(srv) {
        upload_success = false;
        upload_type = "";
        // ekhane dispatcher info add hobe
        // dispatcher().assign("/number/(\\d+)", &hello::number, this, 1);
        // mapper().assign("number", "/number/{1}");
        /*  number is a member function of this (hello), 1 diye bujhacchi ekta param
            i.e. ei type url hole amra this er number method k call dibo
            mapper e dekhtesi: number method tar ki rokom url hobe
        */
        // read_file/type/filename
        dispatcher().assign("/read_file/(\\w+)/(\\w+)", &hello::read_file, this, 1, 2);
        mapper().assign("read_file", "/read_file/{1}/{2}");

        dispatcher().assign("/upload/(\\w+)", &hello::upload, this, 1);
        mapper().assign("upload", "/upload/{1}");

        dispatcher().assign("/mvq/(\\w+)/(\\w+)/(\\d+)", &hello::mvq, this, 1,2,3);
        mapper().assign("mvq", "/mvq/{1}/{2}/{3}");

        dispatcher().assign("/vcm/(\\w+)/(\\d+)/(.*?)/(\\d+)", &hello::vcm, this, 1, 2, 3, 4);//, 1,2,3,4,5,6,7,8,9);
        mapper().assign("vcm", "/vcm/{1}/{2}/{3}/{4}");

        // ei app er jonno default URL
        dispatcher().assign("", &hello::index, this);
        mapper().assign("");

        // root of all urls, eikhane joto dispatch kora hoise shob after root add hobe
        // i.e. /hello/smile dile smile call hobe, /hello dile welcome
        mapper().root("/hello");
        
    }
    vector<string> read_dir(string dir);
    void read_file(string type, string filename);
    void index();
    string intToString(int n);
    void upload(string type);
    void mvq(string ob, string qp, string k_ans);
    void vcm(string ob, string dir, string targetpos, string text);
    // entry point of this application
    // need to remove when using mapping
    // virtual void main(string url);
};

/* runs VCM
    params: ob, obstacle set
            dir, direction of vcm
            targetpos, x1 .. z2, position of target
            text, -1 if simple vcm, otherwise fontsize (for tvcm)
*/

void hello::vcm(string ob, string dir, string targetpos, string text) {
    cout << "Debug: VCM params" << endl;
    cout << ob << " " << dir << " " << targetpos << " " << text << endl;

    string delim = "&";
    size_t pos = 0;
    int c = 0;
    string token;
    double x1, y1, z1, x2, y2, z2;
    while((pos = targetpos.find(delim)) != string::npos) {
        token = targetpos.substr(0, pos);
        if (c == 0) x1 = atof(token.c_str());
        else if (c == 1) y1 = atof(token.c_str());
        else if (c == 2) z1 = atof(token.c_str());
        else if (c == 3) x2 = atof(token.c_str());
        else if (c == 4) y2 = atof(token.c_str());
        else if (c == 5) z2 = atof(token.c_str());
        targetpos.erase(0, pos+delim.length());
        ++c;
    }
    z2 = atof(targetpos.c_str());
    //cout << x1 << " " << y1 << " " << z1 << " " << x2 << " "  << y2 << " " << z2 << endl;


    VCM vcm;
    strcpy(vcm.f, "./ob/");
    strcat(vcm.f, ob.c_str());

    vcm.fontsize = atoi(text);
    if (vcm.fontsize != -1) {
        vcm.argContainsText = true;
    }

    vcm.setup();
    Box b(Vector3(x1, y1, z1), Vector3(x2, y2, z2));
    vcm.setTarget(b);

    vcm.run2(atoi(dir));

    response().out() << "Inside VCM";

}


/* runs MVQ
    params: ob, obstacle set
            qp, querypoints set
            k_ans, number of querypoints to return
*/

void hello::mvq(string ob, string qp, string k_ans) {
    cout << "MVQ " <<ob << " " << qp << " " << k_ans;
    MVQ mvq;
    strcat(mvq.f, "./ob/");
    strcat(mvq.f, ob.c_str());
    strcat(mvq.queryPath, "./qp/");
    strcat(mvq.queryPath, qp.c_str());
    mvq.setup();
    mvq.loadQueryPoints();

    vector<QueryPoint3D> q;
    cppcms::json::value json_obj;
    Point3D cp[8];


    bool s = mvq.Mov_exp3D(atoi(k_ans.c_str()), q, cp);

    for (int i=0;i<8;++i) {
        //cout << cp[i].toStr() << endl;
        json_obj[0]["corner_points"][i] = cp[i].toStr();
    }

    //response().out() << json_obj;

    for (int i=0;i<q.size();++i) {
        //cout << "*** Rank: " << (i+1) << " ***" << endl;
        //q[i].print();
        json_obj[i]["position"] = q[i].getPosition();
        json_obj[i]["visibility"] = q[i].total_visibility;
        json_obj[i]["num_visible_planes"] = q[i].visiblePlanes.size();
        for (int j=0;j<q[i].visiblePlanes.size();++j) {
            json_obj[i]["visible_planes"][j]["planeid"] = q[i].visiblePlanes[j].planeId;
            // for (int k=0;k<4;++k) {
            //     json_obj[i]["visible_planes"][j]["boundary"][k] = q[i].getVisiblePlaneBoundary(j, k);
            // }
            int l = 0;            
            for (list<polygon>::iterator it =
                q[i].visiblePlanes[j].invisible_parts.begin();
                it != q[i].visiblePlanes[j].invisible_parts.end(); ++it, ++l) {
                for (int k = 0; k < it->sides.size(); ++k) {
                    json_obj[i]["visible_planes"][j]["invisible_parts"][l]["boundary"][k] = it->sides[k].a.toStr();
                }
            }
            json_obj[i]["visible_planes"][j]["num_invisible_parts"] = l;
        }
    }
    response().out() << json_obj;
    //cout << s << endl;
    //response().out() << s;
}

/* uploads file to obstacles/querypoints/targetpath dir */
void hello::upload(string type) {
    content::index_content data;
    if (request().request_method() == "POST") {
        data.uploadfile.load(context());
        if (data.uploadfile.validate()) {
            //string fname = data.uploadfile.f.value()->name();
            // cout << fname << endl;
            string fname = data.uploadfile.f.value() -> filename();
            data.uploadfile.f.value() -> save_to("./" + type + "/" + fname);
            
            data.uploadfile.clear();

            upload_success = true;
            upload_type = type;
            
        }
    }
    response().set_redirect_header("/hello");
}

/* reads a file on http request and returns in json */
void hello::read_file(string type, string filename) {
    cout << "Reading file: " << type << " " << filename << endl;
    // modifying path
    string temp = "./";
    temp.append(type);
    temp.append("/");
    temp.append(filename);
    temp.append(".txt");
    cout << temp << endl;

    cppcms::json::value json_object;

    string line;
    ifstream reader(temp.c_str());
    int counter = 0;
    if (reader.is_open()) {
        while (getline(reader, line)) {
            // cout << line << endl;
            // response().out() << line << "<br>";
            if (counter) 
                json_object[intToString(counter)] = line;
            else 
                json_object["size"] = line;
            ++counter;
        }
    }
    //json_object["hello"] = "world";
    //json_object[to_string(1)] = "whoa";
    reader.close();
    response().out() << json_object;
    //cout << json_object;
}

/*
    reads the directory and returns the list of files in it
    @param: dir is the absolute path to the directory
*/
vector<string> hello::read_dir(string dir) {
    // cout << "Reading dir: " << dir << endl;
    vector<string> s;
    tinydir_dir dd;
    tinydir_open(&dd, dir.c_str());
    while (dd.has_next)
    {
        tinydir_file file;
        tinydir_readfile(&dd, &file);
    
        // printf("%s", file.name);
        if (file.is_dir)
        {
            // printf("/");
        }
        else  {
            char *pos = strstr(file.name, ".txt");
            if (pos) {
                *pos = '\0';
                s.push_back(file.name);
                //printf("%s", file.name);
                //printf("\n");
            }
        }
        // printf("\n");
        tinydir_next(&dd);
    }
    
    tinydir_close(&dd);
    // cout << "# of files: " << s.size() << endl;
    return s;
}


string hello::intToString(int n) {
    ostringstream temp;
    temp<<n;
    return temp.str();
}

void hello::index() {
    //response.out() << "Home";
    cout << "Loading index.html" << endl;
    //content::message data;
    content::index_content data;
    // data.text = "<< Hello >>";
    //c.testmap.insert(pair<string, string>("1", "Test 1"));
    //c.testmap.insert(pair<string, string>("2", "Test 2"));

    vector<string> temp;
    temp.push_back("dummy");

    data.ob = read_dir("./ob");
    data.qp = read_dir("./qp");
    data.tp = read_dir("./tp");
    // data.messages = temp;
    if (upload_success) {
        upload_success = false;
        data.messages.push_back("Upload successful");
        // data.upload_success_message.insert(pair<string, string>(upload_type, "Upload successful."));
    }
    data.fontsize = temp;
    render("my_index", "index", data);
}

// void hello::main(string url) {
//     // string s = "hello world";
//     // for (int i=0;i< 10;++i) {
//     //     s.append("hoi");
//     // }
//     // response().out() << 
//     // s;
//     content::message c;
//     c.text = "<< Hello >>";
//     c.c1 = ">> Bye << ";
//     render("message", c);   // message namer view ta k render korbo
// }
// entry point
int main(int argc, char **argv) {
    try {
        // create a new cppcms service
        cppcms::service srv(argc, argv);
        // add applications to current service app pool
        srv.applications_pool().mount(
            cppcms::applications_factory<hello>()
        );
        // run service
        srv.run();
    }
    catch (exception const &e) {
        cerr << e.what() << endl;
    }
}