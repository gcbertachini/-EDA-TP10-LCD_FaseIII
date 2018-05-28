#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "News.h"

typedef unsigned int uint;
using namespace std;

class Feed
{

public:

	void set_source(string source);

	const char * get_feed_title();
	const News * get_next_title();
	const News * get_previous_title();

	void add_news(News* new_news);

	Feed();
	~Feed();

private:
	string source;
	News * current;
	vector <News *> titulares;			

};

