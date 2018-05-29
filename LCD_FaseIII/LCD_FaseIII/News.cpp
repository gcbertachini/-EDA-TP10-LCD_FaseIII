#include "News.h"



News::News()
{
	title = "";
	time = "";
	date = "";
}


News::~News()
{
}


void News::update_title(string title){
	this->title = title;
}

void News::update_date(string date){
	this->date = date;
}
void News::update_time(string time) {
	this->time = time;
}


/***************************************
***************getters******************
****************************************/

string News::get_title()const {
	return title;
}

 string News::get_date()const {
	return date;
}
 string News::get_time() const {
	 return time;
 }
int News::get_title_size() const{
	return title.length();
}
int News::get_date_size()const {
	return date.length();
}
int News::get_time_size() const {
	return time.length();
}
string News::get_date_and_time() const{
	return (date + " - " + time);
}