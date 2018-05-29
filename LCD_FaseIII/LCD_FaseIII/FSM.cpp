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
	user_data->should_add = false;
}

void null_function(my_user_data_t * user_data)
{

}
void add_news_title(my_user_data_t * user_data) {
	user_data->temp_news->update_title(user_data->to_add_data);
	user_data->to_add_data = "";
	user_data->should_add = false;
}

void add_date_and_time(my_user_data_t * user_data) {
	
	const char * ptr;
	
	
	string day = user_data->to_add_data.substr(5, 2);

	string month = user_data->to_add_data.substr(8, 3);

	if (month == "Jan")
		month = "01";
	else if (month == "Feb")
		month = "02";
	else if (month == "Mar")
		month = "03";
	else if (month == "Apr")
		month = "04";
	else if (month == "May")
		month = "05";
	else if (month == "Jun")
		month = "06";
	else if (month == "Jul")
		month = "07";
	else if (month == "Aug")
		month = "08";
	else if (month == "Sep")
		month = "09";
	else if (month == "Oct")
		month = "10";
	else if (month == "Nov")
		month = "11";
	else if (month == "Dec")
		month = "12";

	string year = user_data->to_add_data.substr(14, 2);

	string time = user_data->to_add_data.substr(17, 5);
	
	user_data->temp_news->update_date(day + "/" + month + "/" + year);
	user_data->temp_news->update_time(time);



	user_data->to_add_data = "";
	user_data->should_add = false;
}

void create_news(my_user_data_t * user_data) {
	
}

void insert_news_in_feed(my_user_data_t * user_data) {
	News* to_insert = new News();

	to_insert->update_title(user_data->temp_news->get_title());
	to_insert->update_time(user_data->temp_news->get_time());
	to_insert->update_date(user_data->temp_news->get_date());
	
	user_data->feed->add_news(to_insert);

	user_data->temp_news->update_title("");
	user_data->temp_news->update_date("");
	user_data->temp_news->update_time("");
}

void forget_input(my_user_data_t * user_data) {
	user_data->to_add_data = "";
}

void should_get_data(my_user_data_t * user_data) {
	user_data->should_add = true;
}