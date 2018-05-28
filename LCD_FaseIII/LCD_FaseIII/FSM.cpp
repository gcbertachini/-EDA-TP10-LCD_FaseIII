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
	to_act_on.action(user_data);
	this->current_state = to_act_on.next_state;
}