#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "News.h"
#include "FSM.h"

typedef unsigned int uint;
using namespace std;

class Feed
{

public:

	void set_source(string source);

	const char * get_feed_title();
	const News * get_next_title();
	const News * get_previous_title();

	News * get_current_title();

	void run_filter(Event event);

	void add_news(News* new_news);

	void reset_feed();

	Feed();
	~Feed();

private:
	string source;
	News * current;
	vector <News *> titulares;
	FSM filter;				
	bool XML_Parser(string xml_code);

};

