#pragma once
#include <vector> 
#include "Observer.h"
class Observable
{
public:
	enum class Observable_type {
		client
	};
	Observable(Observable_type identifier);
	~Observable();

	
	void add_observer(Observer* ob);
	Observable_type type;

	void notify_obs();
	
	bool has_new_info();

private:
	bool new_info;
	std::vector<Observer*> obs;

};

