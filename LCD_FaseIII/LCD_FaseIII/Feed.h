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
	const char * get_Feed_Title();
	const News * get_Next_Title();
	const News * get_Previous_Title();
	void run_Filter(Event event);

	Feed();
	~Feed();

private:
	string source;
	News * current;
	vector <News *> titulares;
	const FSM filter;				//en las cosas de clase tiene el [][]
	bool XML_Parser(string xml_code);

};

