#include "Feed.h"



Feed::Feed()
{
	current_pos = -1;
	source = "";
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



/****************************************************
********************get_feed_source******************
*****************************************************
*get_feed_source returns the source of the news feed.
*
*INPUT:
*	1) void. 
*OUTPUT:
*	1) char pointer to the string with the source!
*/
const char * Feed::get_feed_source(){
	return source.c_str();
}


/****************************************************
********************get_next_title*******************
*****************************************************
*get_next_title returns the next news to be shown by the feed 
*in case the feed has not reached its end. NULL pointer if so 
*get_next_title returns the current news being pointed 
*with position current_pos in the News * vector titles
*it also increments current_pos in case of success.
*
*INPUT:
*	1) void.
*OUTPUT:
*	1) pointer to the news to be shown or NULL pointer in case there are no more 
	
*/
const News * Feed::get_next_title(){
	News * returned_news = NULL;

	if ( this->has_more_news() ) {			
		
		try {
			returned_news = titles.at(current_pos);			
			current_pos++;							//watch for the order just in case!
		}
		catch (std::out_of_range o) {

		}
	}
	return returned_news;
}
/****************************************************
********************get_previous_title*******************
*****************************************************
*get_previous_title returns the previous title that has been shown by the feed.
*get_previous_title returns the news that comes before the one being pointed
*with position current_pos in the News * vector titles
*it also increments current_pos in case of success.
*
*INPUT:
*	1) void.
*OUTPUT:
*	1) pointer to the news to be shown or NULL pointer in case there is no previous news available!
*/
const News * Feed::get_previous_title(){

	News * returned_news = NULL;

	if ( (current_pos-1) >= 0 ) {

		try {
			returned_news = titles.at(current_pos-1);
			current_pos--;							//the order is important, because if i decrement current_pos before doing .at() 
													//the change will remain if i catch an exception
		}
		catch (std::out_of_range o) {

		}
	}
	return returned_news;
}

/****************************************************
********************add_news*************************
*****************************************************
*add_news adds news to the feed.
*
*INPUT:
*	1) new_news : news to be added to the feed.
*OUTPUT:
*	1) void.
*/
void Feed::add_news(News* new_news) {
	titles.push_back(new_news);
	if (current_pos == -1)
		current_pos++;
}

/****************************************************
********************is_empty*************************
*****************************************************
*is_empty tells if the feed is empty.
*
*INPUT:
*	1) void.
*OUTPUT:
*	1) bool that is true if the feed is empty, false if not.
*/
bool Feed::is_empty() {
	return (!titles.size()); //will return 1 (true) in case titulares is empty (size == 0), !any other number = 0 (size != 0) in case it's not.
}


/****************************************************
********************has_more_news*****************
*****************************************************
*has_no_more_news tells if there are any more news to be shown by the feed.
*checks if the feed is empty to verify.
*it basically tells the user whether a call to get_next_title will return a NULL
*pointer or not if the feed is not empty.
*
*INPUT:
*	1) void.
*OUTPUT:
*	1) bool that is true if the feed has more news to show, false if not.
*/
bool Feed::has_more_news() {
	return ( ( current_pos< titles.size() ) && ( !this->is_empty() ));
}


/****************************************************
********************reset_feed***********************
*****************************************************
*reset_feed rewinds the feed so that a call to get_next_title
*will give the user a pointer to the first news in the feed.
*reset_feed DOES NOT CLEAR THE FEED! IT DOES NOT DELETE THE 
*NEWS FROM THE FEED!
*
*INPUT:
*	1) void.
*OUTPUT:
*	1) bool that is true if the feed is empty, false if not.
*/
bool Feed::reset_feed() {

	bool is_empty = this->is_empty();

	if (!is_empty) 
		current_pos = 0;
	else 
		current_pos = -1;
	
	return is_empty;
}

/****************************************************
********************clear_feed***********************
*****************************************************
*clear_feed deletes all news from the feed. 
*the source is set to the null string.
*
*INPUT:
*	1) void.
*OUTPUT:
*	1) void.
*/
void Feed::clear_feed() {
	titles.clear();
	current_pos = -1;
	source = "";
}