#include "Feed.h"



Feed::Feed()
{
	current = NULL;
}


Feed::~Feed()
{
}

/***************************************
***************setters******************
****************************************/
void Feed::set_source(string source) {
	this->source = source;
}

/***************************************
***************getters******************
****************************************/
const char * Feed::get_feed_title(){}

const News * Feed::get_next_title(){}

const News * Feed::get_previous_title(){}

News * Feed::get_current_title() {
	return current;
}

void Feed::run_filter(Event event){

}

void Feed::add_news(News* new_news) {
	titulares.push_back(new_news);
}

bool Feed::XML_Parser(string xml_code) {

}
