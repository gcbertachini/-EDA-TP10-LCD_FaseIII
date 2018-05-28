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
const char * Feed::get_feed_title(){
	
}

const News * Feed::get_next_title(){}

const News * Feed::get_previous_title(){}


void Feed::add_news(News* new_news) {
	titulares.push_back(new_news);
}

