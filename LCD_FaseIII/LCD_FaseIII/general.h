#pragma once
typedef struct {

	Feed * feed;

	string to_add_data = "";			//data to be added to a new News object, which will later on be added to the feed.
										//Note that whenever there s a change in the fsm current state, to_add_data will be added to the feed and should then be set to "".

} my_user_data_t;