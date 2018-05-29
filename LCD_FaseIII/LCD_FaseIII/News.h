#pragma once
#include <iostream>
#include <string>

typedef unsigned int uint;
using namespace std;


class News
{

public:
	News();
	~News();


	string get_title() const;
	string get_date()const;
	string get_time() const;

	string get_date_and_time() const;

	void update_title(string title);
	void update_date(string date);
	void update_time(string time);

	int get_title_size() const;
	int get_date_size() const;
	int get_time_size() const;
	
	


private:
	string title;
	string date;
	string time;
};