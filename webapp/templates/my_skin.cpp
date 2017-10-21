#line 1 "./templates/my_skin.tmpl"
#include "../content.h" 
#line 2 "./templates/my_skin.tmpl"
namespace my_skin {
	#line 3 "./templates/my_skin.tmpl"
	struct message :public cppcms::base_view
	#line 3 "./templates/my_skin.tmpl"
	{
	#line 3 "./templates/my_skin.tmpl"
		content::message &content;
	#line 3 "./templates/my_skin.tmpl"
		message(std::ostream &_s,content::message &_content): cppcms::base_view(_s),content(_content)
	#line 3 "./templates/my_skin.tmpl"
		{
	#line 3 "./templates/my_skin.tmpl"
		}
		#line 5 "./templates/my_skin.tmpl"
		virtual void render() {
			#line 8 "./templates/my_skin.tmpl"
			out()<<"\n"
				"<html>\n"
				"    <body>\n"
				"    <h1>";
			#line 8 "./templates/my_skin.tmpl"
			out()<<cppcms::filters::escape(content.text);
			#line 9 "./templates/my_skin.tmpl"
			out()<<" World! </h1>\n"
				"    ";
			#line 9 "./templates/my_skin.tmpl"
			if((content.dict).begin()!=(content.dict).end()) {
				#line 10 "./templates/my_skin.tmpl"
				out()<<"\n"
					"        ";
				#line 10 "./templates/my_skin.tmpl"
				for(CPPCMS_TYPEOF((content.dict).begin()) d_ptr=(content.dict).begin(),d_ptr_end=(content.dict).end();d_ptr!=d_ptr_end;++d_ptr) {
				#line 10 "./templates/my_skin.tmpl"
				CPPCMS_TYPEOF(*d_ptr) &d=*d_ptr;
					#line 11 "./templates/my_skin.tmpl"
					out()<<"\n"
						"            <h2>";
					#line 11 "./templates/my_skin.tmpl"
					out()<<cppcms::filters::escape(d.first);
					#line 12 "./templates/my_skin.tmpl"
					out()<<"</h2> <br>\n"
						"            ";
					#line 12 "./templates/my_skin.tmpl"
					if((d.second).begin()!=(d.second).end()) {
						#line 13 "./templates/my_skin.tmpl"
						out()<<"\n"
							"                ";
						#line 13 "./templates/my_skin.tmpl"
						for(CPPCMS_TYPEOF((d.second).begin()) second_ptr=(d.second).begin(),second_ptr_end=(d.second).end();second_ptr!=second_ptr_end;++second_ptr) {
						#line 13 "./templates/my_skin.tmpl"
						CPPCMS_TYPEOF(*second_ptr) &second=*second_ptr;
							#line 14 "./templates/my_skin.tmpl"
							out()<<"\n"
								"                    ";
							#line 14 "./templates/my_skin.tmpl"
							out()<<cppcms::filters::escape(second);
							#line 15 "./templates/my_skin.tmpl"
							out()<<" <br>\n"
								"                ";
						#line 15 "./templates/my_skin.tmpl"
						} // end of item
						#line 16 "./templates/my_skin.tmpl"
						out()<<"\n"
							"            ";
					#line 16 "./templates/my_skin.tmpl"
					}
					#line 17 "./templates/my_skin.tmpl"
					out()<<"\n"
						"        ";
				#line 17 "./templates/my_skin.tmpl"
				} // end of item
				#line 18 "./templates/my_skin.tmpl"
				out()<<"\n"
					"    ";
			#line 18 "./templates/my_skin.tmpl"
			}
			#line 21 "./templates/my_skin.tmpl"
			out()<<"\n"
				"    </body>\n"
				"</html>\n"
				"";
		#line 21 "./templates/my_skin.tmpl"
		} // end of template render
	#line 22 "./templates/my_skin.tmpl"
	}; // end of class message
#line 23 "./templates/my_skin.tmpl"
} // end of namespace my_skin
#line 23 "./templates/my_skin.tmpl"
namespace {
#line 23 "./templates/my_skin.tmpl"
 cppcms::views::generator my_generator; 
#line 23 "./templates/my_skin.tmpl"
 struct loader { 
#line 23 "./templates/my_skin.tmpl"
  loader() { 
#line 23 "./templates/my_skin.tmpl"
   my_generator.name("my_skin");
#line 23 "./templates/my_skin.tmpl"
   my_generator.add_view<my_skin::message,content::message>("message",true);
#line 23 "./templates/my_skin.tmpl"
    cppcms::views::pool::instance().add(my_generator);
#line 23 "./templates/my_skin.tmpl"
 }
#line 23 "./templates/my_skin.tmpl"
 ~loader() {  cppcms::views::pool::instance().remove(my_generator); }
#line 23 "./templates/my_skin.tmpl"
} a_loader;
#line 23 "./templates/my_skin.tmpl"
} // anon 
