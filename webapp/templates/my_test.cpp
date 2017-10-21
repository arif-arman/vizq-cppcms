#line 1 "./templates/my_test.tmpl"
#include "../content.h" 
#line 2 "./templates/my_test.tmpl"
namespace my_test {
	#line 3 "./templates/my_test.tmpl"
	struct test :public cppcms::base_view
	#line 3 "./templates/my_test.tmpl"
	{
	#line 3 "./templates/my_test.tmpl"
		content::message &content;
	#line 3 "./templates/my_test.tmpl"
		test(std::ostream &_s,content::message &_content): cppcms::base_view(_s),content(_content)
	#line 3 "./templates/my_test.tmpl"
		{
	#line 3 "./templates/my_test.tmpl"
		}
		#line 5 "./templates/my_test.tmpl"
		virtual void render() {
			#line 10 "./templates/my_test.tmpl"
			out()<<"\n"
				"\n"
				"<html>\n"
				"<body>\n"
				"<!--\n"
				"";
			#line 10 "./templates/my_test.tmpl"
			if(!(content.name.empty())) {
				#line 11 "./templates/my_test.tmpl"
				out()<<"\n"
					"    <h1>Hello ";
				#line 11 "./templates/my_test.tmpl"
				out()<<cppcms::filters::escape(content.name);
				#line 12 "./templates/my_test.tmpl"
				out()<<"</h1>\n"
					"";
			#line 12 "./templates/my_test.tmpl"
			}else{
				#line 15 "./templates/my_test.tmpl"
				out()<<"\n"
					"-->\n"
					"<form method=\"post\" action=\"\" enctype=\"multipart/form-data\">\n"
					"";
				#line 15 "./templates/my_test.tmpl"
				{ cppcms::form_context _form_context(out(),cppcms::form_flags::as_html,cppcms::form_flags::as_p); (content.uploadfile).render(_form_context); }
				#line 17 "./templates/my_test.tmpl"
				out()<<"\n"
					"</form>\n"
					"<!-- ";
			#line 17 "./templates/my_test.tmpl"
			}
			#line 21 "./templates/my_test.tmpl"
			out()<<" -->\n"
				"</body>\n"
				"</html>\n"
				"\n"
				"";
		#line 21 "./templates/my_test.tmpl"
		} // end of template render
	#line 22 "./templates/my_test.tmpl"
	}; // end of class test
#line 23 "./templates/my_test.tmpl"
} // end of namespace my_test
#line 23 "./templates/my_test.tmpl"
namespace {
#line 23 "./templates/my_test.tmpl"
 cppcms::views::generator my_generator; 
#line 23 "./templates/my_test.tmpl"
 struct loader { 
#line 23 "./templates/my_test.tmpl"
  loader() { 
#line 23 "./templates/my_test.tmpl"
   my_generator.name("my_test");
#line 23 "./templates/my_test.tmpl"
   my_generator.add_view<my_test::test,content::message>("test",true);
#line 23 "./templates/my_test.tmpl"
    cppcms::views::pool::instance().add(my_generator);
#line 23 "./templates/my_test.tmpl"
 }
#line 23 "./templates/my_test.tmpl"
 ~loader() {  cppcms::views::pool::instance().remove(my_generator); }
#line 23 "./templates/my_test.tmpl"
} a_loader;
#line 23 "./templates/my_test.tmpl"
} // anon 
