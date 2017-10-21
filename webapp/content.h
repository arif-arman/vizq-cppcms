#include <cppcms/view.h>
#include <cppcms/form.h>
#include <string>
#include <vector>
#include <cppcms/http_file.h>
using namespace std;
namespace content {

    struct uploadfile_form: public cppcms::form {
        cppcms::widgets::file f;
        cppcms::widgets::submit submit;
        uploadfile_form() {
            submit.value("Send");
            
            //f.message("File to upload");
            //f.help(".txt only");
            f.non_empty();
            add(f);

            //add(submit);            
        }
        // virtual bool validate() {
            //if (!form::validate) return false;
            //if (f.value() -> filename().find(".txt") < f.value() -> filename().length) return true;
            //return false;
        //}
    };
    
    struct message: public cppcms::base_content {
        string text;
        string name, pass;
        uploadfile_form uploadfile;
        
    };
    
    struct index_content: public cppcms::base_content {
        // map<string, vector<string> > dict;
        vector<string> ob;
        vector<string> qp;
        vector<string> tp;
        vector<string> messages;
        vector<string> fontsize;
        uploadfile_form uploadfile;

        
    };

    struct test_message: public cppcms::base_content {
    	string text;
    };

    


}
