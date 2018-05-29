#include "FSM.h"



FSM::FSM()
{
	this->current_state = State::IDDLE;
}


FSM::~FSM()
{
}


void FSM::act_on_event(Event received_event, my_user_data_t * user_data) {
	cell to_act_on = get_cell(this->current_state, received_event);
	to_act_on.action(user_data);					//executes the action routine.
	this->current_state = to_act_on.next_state;		//makes the state transition.
}


//Action routines!
void add_source(my_user_data_t * user_data) {
	user_data->feed->set_source(user_data->to_add_data);
	user_data->to_add_data = "";
}

void null_function(my_user_data_t * user_data)
{

}
void add_news_title(my_user_data_t * user_data) {
	user_data->temp_news->update_title(user_data->to_add_data);
	user_data->to_add_data = "";
}

void add_date_and_time(my_user_data_t * user_data) {
	string date, time;
	//date = user_data->to_add_data ...				//need a function call that splits the string!!!
	//time = user_data->to_add_data...

	user_data->temp_news->update_date(date);
	user_data->temp_news->update_time(time);
	user_data->to_add_data = "";
}

void create_news(my_user_data_t * user_data) {
	if (user_data->temp_news != NULL) {
		News * temp = new News();
		user_data->temp_news = temp;
	}
}

void insert_news_in_feed(my_user_data_t * user_data) {
	user_data->feed->add_news(user_data->temp_news);
	user_data->temp_news = NULL;					//reset the pointer so that other news can be created.
}

void forget_input(my_user_data_t * user_data) {
	user_data->to_add_data = "";
}