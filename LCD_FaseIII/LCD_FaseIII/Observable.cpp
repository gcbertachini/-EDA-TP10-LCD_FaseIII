#include "Observable.h"



Observable::Observable(Observable_type identifier)
{
	type = identifier;
	new_info = false;
}


Observable::~Observable()
{
}
void Observable::add_observer(Observer* ob) {
	obs.push_back(ob);
}
void Observable::notify_obs() {
	new_info = true;
	for (std::vector<Observer*>::iterator it = obs.begin(); it != obs.end(); ++it) {
		(*it)->update(this);
	}
	new_info = false;
}

bool Observable::has_new_info() {
	return new_info;
}
