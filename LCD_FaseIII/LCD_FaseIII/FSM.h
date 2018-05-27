#pragma once
#define EV_AMOUNT	10
#define ES_AMOUUNT	7

enum class State	{IDDLE,CHANNEL,ITEM,OTHER_ITEM,ITEM_DATE,ITEM_TITLE,CH_TITLE};
enum class Event	{CH_TAG,CH_TAG_TERMINATOR,TITLE_TAG, TITLE_TAG_TERMINATOR, ITEM_TAG, ITEM_TAG_TERMINATOR, PUB_DATE, PUB_DATE_TERMINATOR, OTHER_TAG, OTHER_TAG_TERMINATOR};


struct cell {
	State next_state;
	void(*action)(void *);
};
class FSM
{
private:
	const cell tabla[ES_AMOUUNT][EV_AMOUNT] = { //State_Table
				//CH_TAG							  CH_TAG_TERMINATOR							TITLE_TAG							   TITLE_TAG_TERMINATOR							ITEM_TAG						 ITEM_TAG_TERMINATOR							PUB_DATE							 PUB_DATE_TERMINATOR					     OTHER_TAG							 OTHER_TAG_TERMINATOR
		{	{ State::CHANNEL , rut1 },			 { State::IDDLE , null_function },		{ State::IDDLE , null_function },        { State::IDDLE , null_function },		 { State::IDDLE , null_function },		{ State::IDDLE , null_function },		{ State::IDDLE , null_function },		  { State::IDDLE , null_function },			 { State::IDDLE , null_function },		  { State::IDDLE , null_function }	}, //IDDLE state

		{	{ State::CHANNEL , null_function },  { State::IDDLE , null_function },	    { State::CH_TITLE , null_function },	 { State::CHANNEL , null_function },	 { State::ITEM , null_function },   	{ State::CHANNEL , null_function },		{ State::CHANNEL , null_function },		  { State::CHANNEL , null_function },		 { State::CHANNEL , null_function },	  { State::CHANNEL , null_function } }, //CHANNEL state

		{	{ State::CH_TITLE , rut1 },			 { State::CH_TITLE , null_function },   { State::CH_TITLE , null_function },	 { State::CHANNEL , null_function },    { State::CH_TITLE , null_function },    { State::CH_TITLE , null_function },	{ State::CH_TITLE , null_function },      { State::CH_TITLE , null_function },		 { State::CH_TITLE , null_function },	  { State::CH_TITLE , null_function } }, //CH_TITLE state

		{	{ State::ITEM , rut1 },				 { State::ITEM , null_function },	    { State::ITEM_TITLE , null_function },   { State::ITEM , null_function },        { State::ITEM , null_function },		{ State::CHANNEL , null_function },		{ State::ITEM_DATE , null_function },     { State::ITEM , null_function },			 { State::OTHER_ITEM , null_function },   { State::ITEM , null_function } }, //ITEM state

		{	{ State::OTHER_ITEM , rut1 },		 { State::OTHER_ITEM , null_function }, { State::OTHER_ITEM , null_function },   { State::OTHER_ITEM , null_function },  { State::OTHER_ITEM , null_function }, { State::OTHER_ITEM , null_function },  { State::OTHER_ITEM , null_function },    { State::OTHER_ITEM , null_function },	 { State::OTHER_ITEM , null_function },   { State::ITEM , null_function } }, //OTHER_ITEM state

		{	{ State::ITEM_TITLE  , rut1 },		 { State::ITEM_TITLE , null_function }, { State::ITEM_TITLE , null_function },   { State::ITEM , null_function },		 { State::ITEM_TITLE , null_function }, { State::ITEM_TITLE , null_function },  { State::ITEM_TITLE , null_function },    { State::ITEM_TITLE , null_function },	 { State::ITEM_TITLE , null_function },   { State::ITEM_TITLE , null_function } }, //ITEM_TITLE state

		{	{ State::ITEM_DATE , rut1 },		 { State::ITEM_DATE , null_function },  { State::ITEM_DATE , null_function },    { State::ITEM_DATE , null_function },   { State::ITEM_DATE , null_function },  { State::ITEM_DATE , null_function },   { State::ITEM_DATE , null_function },     { State::ITEM , null_function },			 { State::ITEM_DATE , null_function },    { State::ITEM_DATE , null_function } } //ITEM_DATE state

	};
	uint index;

public:
	FSM();
	~FSM();

};

//Rutinas de acción

	void rut1(void *) {

	}

	void null_function(void *)
	{

	}
