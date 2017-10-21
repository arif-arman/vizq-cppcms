{
    "service" : {
        "api" : "http",
        "post" : 8080
    },
    "http" : {
        "script_names" : [ "/hello", "/testground" ]
    }, 
    "views" : {
        "paths" : ["./templates"],
        "skins" : ["my_index", "my_test"]
    },
    "file_server" : {
        "enable" : true,
        "listing" : true,
        "document_root" : "./static"
     },
     "security" : {  
        "csrf" : {  
           "enable" : false  
        }  
     }  
}