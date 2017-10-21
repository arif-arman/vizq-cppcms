#include <cppcms/application.h>
#include <cppcms/applications_pool.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
#include <cppcms/http_file.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cppcms/url_dispatcher.h>
#include <cppcms/url_mapper.h>
#include <fstream>
#include <sstream>
#include "content.h"
#include "tinydir.h"

#define SOME_PAIR(x,y) make_pair(string(x), vector<string>(y))


using namespace std;
// an application, we may need to create similar classes for other apps
class testground: public cppcms::application {
public:
    testground(cppcms::service &srv): cppcms::application(srv) {
        // ekhane dispatcher info add hobe
        // dispatcher().assign("/number/(\\d+)", &testground::number, this, 1);
        // mapper().assign("number", "/number/{1}");
        /*  number is a member function of this (testground), 1 diye bujhacchi ekta param
            i.e. ei type url hole amra this er number method k call dibo
            mapper e dekhtesi: number method tar ki rokom url hobe
        */
        // read_file/type/filename
        

        // ei app er jonno default URL
        dispatcher().assign("", &testground::index, this);
        mapper().assign("");

        // root of all urls, eikhane joto dispatch kora hoise shob after root add hobe
        // i.e. /testground/smile dile smile call hobe, /testground dile welcome
        mapper().root("/testground");
        
    }
    void index();
};

void testground::index() {
    //response.out() << "Home";
    cout << "Entered testground" << endl;
    //response().out() << "Entered testground";
    //content::message data;
    //content::index_content data;
    // data.text = "<< testground >>";
    //c.testmap.insert(pair<string, string>("1", "Test 1"));
    //c.testmap.insert(pair<string, string>("2", "Test 2"));

    content::message data;
    if (request().request_method() == "POST") {
        data.uploadfile.load(context());
        if (data.uploadfile.validate()) {
            //data.name = data.uploadfile.name.value();
            //data.pass = data.uploadfile.pass.value();
            string val = "val.txt";
            data.uploadfile.f.value()->save_to("./test/" + val);

            data.uploadfile.clear();
        }
    }
    render("my_test", "test", data);
}


// entry point
int main(int argc, char **argv) {
    try {
        // create a new cppcms service
        cppcms::service srv(argc, argv);
        // add applications to current service app pool
        srv.applications_pool().mount(
            cppcms::applications_factory<testground>()
        );
        // run service
        srv.run();
    }
    catch (exception const &e) {
        cerr << e.what() << endl;
    }
}