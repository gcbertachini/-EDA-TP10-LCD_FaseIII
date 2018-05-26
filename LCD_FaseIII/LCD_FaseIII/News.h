#pragma once
#include <iostream>
#include <string>

typedef unsigned int uint;
using namespace std;

class News
{
private:
	string Title;
	string Date;

public:
	News();
	~News();
	char * get_Title();
	char * get_Date();
	void update_Title(char * title, uint index);
	void update_Date(char * title, uint index);
	void curren_Title(char s, uint index);
	void curren_Date(char s, uint index);
	int get_Title_size();
	int get_Date_size();


};

