#pragma once

#include "general.h"
#include <stdio.h>
#include "expat.h"
#include "LCDHitachi.h"
#include "xml_getter.h"
#include "FSM.h" 
#include "Feed.h"
#include "FuncionesGenerales.h"
#include "EventManager.h"

void char_data(void *userData, const XML_Char *s, int len);
void start_tag(void *userData, const XML_Char *name, const XML_Char **atts);
void end_tag(void *userData, const XML_Char *name);

int main(void){

	my_user_data_t user_data;
	LCDHitachi * LCD = new LCDHitachi;
	FuncionesGenerales func(*LCD);

	if (LCD->lcdInitOk()){
		XML_Parser parser;
		XML_Status status;
		LCD->lcdClear();
		//hacer función marquesina
		FSM fsm;
		user_data.fsm = &fsm;
		Feed news_feed;
		user_data.feed = &news_feed;			//should check this constructor!

		parser = XML_ParserCreate(NULL);
		XML_SetElementHandler(parser, start_tag, end_tag);		//Sets handlers for start and end tags: callback functions.
		XML_SetCharacterDataHandler(parser, char_data);			//Sets handler for text.
		XML_SetUserData(parser, &user_data);					


		xml_getter my_xml_getter("rss.nytimes.com/services/xml/rss/nyt/HomePage.xml");
		my_xml_getter.add_observer(&func);

		if (my_xml_getter.getXml()){
			string xml_file = my_xml_getter.returnXml();

			if (xml_file.size() != 0) {

				cout << xml_file << endl;
				const char * buffer = xml_file.c_str();	
				XML_Parse(parser, buffer, xml_file.size(), true);

				//starts displaying news!
				if (!news_feed.is_empty())
				{
					EventManager manager(&func, &news_feed);
					while (news_feed.has_more_news()) {
						func.resetCounter();
						bool displaying_current_news = true;
						News * to_show = (News*)news_feed.get_next_title();			//news to show on the display
						while (displaying_current_news) {										//displaying the news
							if (manager.receive_event()) {
								to_show = (News*)manager.handle_event();				//changes the news to be shown if the user presses a key 
								func.resetCounter();									//resets the marquesina whenever the news to be shown are changed!
							}
							displaying_current_news = !func.marquesina(to_show->get_title(), 0);		//shows the title on the LCD
																										//and verifies if the current news has been completely shown on the display
							func.imprimirFecha(to_show->get_date_and_time());
						}
					}
				}
				else {
					//inform the user there are no news to show on the LCD!!!
					string str = "NO NEWS TO SHOW!";
					unsigned char * pdm = (unsigned char *)str.c_str();
					*LCD << pdm;
				}
			}
		}
	XML_ParserFree(parser);
	}
		
	
	delete LCD;

	return 0;
}

void start_tag(void *userData, const XML_Char *name, const XML_Char **atts) {

	my_user_data_t * my_user_data = (my_user_data_t *) userData;

	Event received_event;

	string received_name = string(name);			//this call to a string constructor makes comparissons easier and addapts to the my_user_data_t struct requirements. 
	cout << "Start tag : " + received_name << endl;
	//getchar();
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

	
	FSM * fsm = (FSM*) my_user_data->fsm;
	fsm->act_on_event(received_event, my_user_data);

	
}
void end_tag(void *userData, const XML_Char *name) {

	my_user_data_t * my_user_data = (my_user_data_t *)userData;

	Event received_event;

	string received_name = string(name); //this call to a string constructor makes comparissons easier and addapts to the my_user_data_t struct requirements.

	cout << "End tag : " + received_name << endl;
	//getchar();
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

	FSM * fsm = (FSM*)my_user_data->fsm;
	fsm->act_on_event(received_event, my_user_data); //reacts to the new event. Possibly changing feed data
	
}

//NOT zero terminated. You have to use the length argument to deal with the end of the string. 
void char_data(void *userData, const XML_Char *s, int len) {			

	my_user_data_t * my_user_data = (my_user_data_t *)userData;
	if (my_user_data->should_add) {
		string received_str = string(s, len);
		//cout << "Char : "<< len << endl;
		cout << "Char : " + received_str << endl;

		//getchar();
		my_user_data->to_add_data += received_str;		//i add the new info to the last thing i received. 
														//Note that whenever there s a change in the fsm current state, to_add_data should be set to "" for this to work!
	}


}



