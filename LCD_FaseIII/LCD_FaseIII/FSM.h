#pragma once
#define EV_AMOUNT	10
#define ES_AMOUUNT	7
#include "general.h"

//FIJARSE QUE EL ORDEN DE LOS ESTADOS SE CORRESPONDA CON LAS FILAS DE LA TABLAAA!!!
enum class State	{IDDLE, CHANNEL, CH_TITLE, ITEM, OTHER_ITEM, ITEM_TITLE, ITEM_DATE};	
//FIJARSE QUE EL ORDEN DE LOS EVENTOS SE CORRESPONDA CON LAS COLUMNAS DE LA TABLAAA!!!
enum class Event	{CH_TAG, CH_TAG_TERMINATOR, TITLE_TAG, TITLE_TAG_TERMINATOR, ITEM_TAG, ITEM_TAG_TERMINATOR, PUB_DATE, PUB_DATE_TERMINATOR, OTHER_TAG, OTHER_TAG_TERMINATOR};


struct cell {
	State next_state;
	void(*action)(my_user_data_t *);
};



void add_source(my_user_data_t * user_data);
void null_function(my_user_data_t * user_data);
void add_news_title(my_user_data_t * user_data);
void add_date_and_time(my_user_data_t * user_data);
void create_news(my_user_data_t * user_data);
void insert_news_in_feed(my_user_data_t * user_data);
void forget_input(my_user_data_t * user_data);
void should_get_data(my_user_data_t * user_data);

class FSM
{

public:

	void act_on_event(Event received_event, my_user_data_t * user_data);
	FSM();
	~FSM();

private:

	State current_state; 

	const cell tabla[ES_AMOUUNT][EV_AMOUNT] = { //State_Table
				//CH_TAG							  CH_TAG_TERMINATOR							TITLE_TAG							   TITLE_TAG_TERMINATOR							ITEM_TAG						 ITEM_TAG_TERMINATOR							PUB_DATE							 PUB_DATE_TERMINATOR					     OTHER_TAG							 OTHER_TAG_TERMINATOR
		{	{ State::CHANNEL , null_function },			{ State::IDDLE , null_function },		{ State::IDDLE , null_function },        { State::IDDLE , null_function },		 { State::IDDLE , null_function },		{ State::IDDLE , null_function },			{ State::IDDLE , null_function },		{ State::IDDLE , null_function },			 { State::IDDLE , null_function },		  { State::IDDLE , null_function }	}, //IDDLE state

		{	{ State::CHANNEL , null_function },			{ State::IDDLE , null_function },		{ State::CH_TITLE , should_get_data },	 { State::CHANNEL , null_function },	 { State::ITEM , create_news },   	{ State::CHANNEL , null_function },				{ State::CHANNEL , null_function }, 	{ State::CHANNEL , null_function },		 { State::CHANNEL , null_function },	  { State::CHANNEL , null_function } }, //CHANNEL state

		{	{ State::CH_TITLE , null_function },		{ State::CH_TITLE , null_function },	{ State::CH_TITLE , null_function },	 { State::CHANNEL , add_source },	{ State::CH_TITLE , null_function },    { State::CH_TITLE , null_function },			{ State::CH_TITLE , null_function },	{ State::CH_TITLE , null_function },		 { State::CH_TITLE , null_function },	  { State::CH_TITLE , null_function } }, //CH_TITLE state

		{	{ State::ITEM , null_function },			{ State::ITEM , null_function },	    { State::ITEM_TITLE , should_get_data },   { State::ITEM , null_function },        { State::ITEM , null_function },		{ State::CHANNEL , insert_news_in_feed },	{ State::ITEM_DATE , should_get_data },	{ State::ITEM , null_function },			 { State::OTHER_ITEM , null_function },   { State::ITEM , null_function } }, //ITEM state

		{	{ State::OTHER_ITEM , null_function },		{ State::OTHER_ITEM , null_function },	{ State::OTHER_ITEM , null_function },   { State::OTHER_ITEM , null_function },  { State::OTHER_ITEM , null_function }, { State::OTHER_ITEM , null_function },		{ State::OTHER_ITEM , null_function },  { State::OTHER_ITEM , null_function },	 { State::OTHER_ITEM , null_function },   { State::ITEM , forget_input } }, //OTHER_ITEM state

		{	{ State::ITEM_TITLE  , null_function },		{ State::ITEM_TITLE , null_function },	{ State::ITEM_TITLE , null_function },   { State::ITEM , add_news_title },		 { State::ITEM_TITLE , null_function }, { State::ITEM_TITLE , null_function },		{ State::ITEM_TITLE , null_function },  { State::ITEM_TITLE , null_function },	 { State::ITEM_TITLE , null_function },   { State::ITEM_TITLE , null_function } }, //ITEM_TITLE state

		{	{ State::ITEM_DATE , null_function },		{ State::ITEM_DATE , null_function },	{ State::ITEM_DATE , null_function },    { State::ITEM_DATE , null_function },   { State::ITEM_DATE , null_function },  { State::ITEM_DATE , null_function },		{ State::ITEM_DATE , null_function },   { State::ITEM , add_date_and_time },	 { State::ITEM_DATE , null_function },    { State::ITEM_DATE , null_function } } //ITEM_DATE state

	};
	//the definition and declaration of the function goes here so as to explicitly let you know that the state and event enum classes correspond to the row and column indexes respectively.
	cell get_cell (State state, Event event) {
		return this->tabla[(int ) state][(int) event];
	}

};




