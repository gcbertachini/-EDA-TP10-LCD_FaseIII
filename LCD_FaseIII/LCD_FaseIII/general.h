#pragma once


#include "News.h"
#include "Feed.h"

typedef struct {
	
	Feed * feed;						
	News * const temp_news = new News();					//news that will be filled when parsing. After the parsing of a particular news is finished, 
										//this news will be added to the feed by the fsm and temp_news will be resetted.
	void * fsm;							//to avoid circularity
	std::string to_add_data;					//data to be added to a new News object, which will later on be added to the feed.
										//Note that whenever there s a change in the fsm current state, to_add_data will be added to the feed and should then be set to "".
	bool should_add = false;
} my_user_data_t;