#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "News.h"

typedef unsigned int uint;
using namespace std;

//check documentation for in .cpp!!! 
class Feed
{

public:

	void set_source(string source);

	const char * get_feed_source();
	const News * get_next_title();
	const News * get_previous_title();

	void add_news(News* new_news);

	bool is_empty();

	bool has_more_news();
	bool reset_feed();
	void clear_feed();

	Feed();
	~Feed();

private:

	string source;
	vector <News *> titles;
	int current_pos;			//position in the vector for the current title

};

