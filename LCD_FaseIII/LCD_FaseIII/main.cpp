#include <stdio.h>
#include "expat.h"

#include "Feed.h"
#include "FSM.h"
#include "general.h"

void start_tag(void *userData, const XML_Char *name, const XML_Char **atts);
void end_tag(void *userData, const XML_Char *name);
void char_data(void *userData, const XML_Char *s, int len);



int main(void)
{


	FILE * my_file = NULL;

	XML_Parser parser;
	XML_Status status;
	my_user_data_t user_data;
	Feed news_feed;
	user_data.feed = &news_feed;			//should check this constructor!

	parser = XML_ParserCreate(NULL);			//should call XML_ParserFree(); before ending the program!
	XML_SetElementHandler(parser, start_tag, end_tag);		//Sets handlers for start and end tags.
	XML_SetCharacterDataHandler(parser, char_data);			//Sets handler for text.
	XML_SetUserData(parser, &user_data);					

	char * buffer = NULL;
	my_file = fopen("ejemplo.xml", "rb");
	if (my_file != NULL) {

		fseek(my_file, 0L, SEEK_END);			//gets the file pointer to the end of the file.
		int file_size = ftell(my_file);			//gets the size of the file by getting the pointer's current position
		rewind(my_file);						//goes back to the beginning of the file.

		buffer = (char *)malloc(file_size * sizeof(char));
		if (buffer != NULL) {
			fread(buffer, sizeof(char), file_size, my_file);
			XML_Parse(parser, buffer, file_size, true);
		}

	}

	XML_ParserFree(parser);
	free(buffer);
	fclose(my_file);

	return 0;

}

void start_tag(void *userData, const XML_Char *name, const XML_Char **atts) {

	my_user_data_t * my_user_data= (my_user_data_t *) userData;

	Event received_event;

	string received_name = string(name);			//this call to a string constructor makes comparissons easier and addapts to the my_user_data_t struct requirements. 

	if (received_name == "channel")
		received_event = Event::CH_TAG;
	else if(received_name == "item")
		received_event = Event::ITEM_TAG;
	else if (received_name == "title")
		received_event = Event::TITLE_TAG;
	else if (received_name == "pubDate")
		received_event = Event::PUB_DATE;
	else 
		received_event = Event::OTHER_TAG;
	

	my_user_data->feed->run_filter(received_event);			//reacts to the new event. 

	
}
void end_tag(void *userData, const XML_Char *name) {

	my_user_data_t * my_user_data = (my_user_data_t *)userData;

	Event received_event;

	string received_name = string(name); //this call to a string constructor makes comparissons easier and addapts to the my_user_data_t struct requirements.

	if (received_name == "channel")
		received_event = Event::CH_TAG_TERMINATOR;
	else if (received_name == "item")
		received_event = Event::ITEM_TAG_TERMINATOR;
	else if (received_name == "title")
		received_event = Event::TITLE_TAG_TERMINATOR;
	else if (received_name == "pubDate")
		received_event = Event::PUB_DATE_TERMINATOR;
	else 
		received_event = Event::OTHER_TAG_TERMINATOR;

	my_user_data->feed->run_filter(received_event); //reacts to the new event. Possibly changing feed data
	
}

//NOT zero terminated. You have to use the length argument to deal with the end of the string. 
void char_data(void *userData, const XML_Char *s, int len) {			

	my_user_data_t * my_user_data = (my_user_data_t *)userData;

	string received_str = string(s);		
	my_user_data->to_add_data += received_str;		//i add the new info to the last thing i received. 
													//Note that whenever there s a change in the fsm current state, to_add_data should be set to "" for this to work! 

}



