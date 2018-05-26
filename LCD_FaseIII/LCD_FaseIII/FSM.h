#pragma once
#define EV	10
#define ES	7

enum class State	{IDDLE,CHANNEL,ITEM,OTHER_ITEM,ITEM_DATE,ITEM_TITLE,CH_TITLE};
enum class Event	{CH_TAG,CH_TAG_TERMINATOR,TITLE_TAG, TITLE_TAG_TERMINATOR, ITEM_TAG, ITEM_TAG_TERMINATOR, PUB_DATE, PUB_DATE_TERMINATOR, OTHER_TAG, OTHER_TAG_TERMINATOR
};


struct cell {
	State next_state;
	void(*action)(void *);

};
class FSM
{
private:
	const cell tabla[ES][EV] = {
				//CH_TAG				CH_TAG_TERMINATOR							TITLE_TAG, TITLE_TAG_TERMINATOR, ITEM_TAG, ITEM_TAG_TERMINATOR, PUB_DATE, PUB_DATE_TERMINATOR, OTHER_TAG, OTHER_TAG_TERMINATOR
		{	{ State::CHANNEL , rut1 }, { State::IDDLE , null_function() }, { State::IDDLE , null_function() }, { State::IDDLE , null_function() }, { State::IDDLE , null_function() }, { State::IDDLE , null_function() }, { State::IDDLE , null_function() }, { State::IDDLE , null_function() }, { State::IDDLE , null_function() }, { State::IDDLE , null_function() }	}, //IDDLE state
		{	{ CHANNEL , rut1 }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() } }, //IDDLE state
		{	{ CHANNEL , rut1 }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() } }, //IDDLE state
		{	{ CHANNEL , rut1 }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() } }, //IDDLE state
		{	{ CHANNEL , rut1 }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() } }, //IDDLE state
		{	{ CHANNEL , rut1 }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() } }, //IDDLE state
		{	{ CHANNEL , rut1 }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() }, { IDDLE , null_function() } } //IDDLE state

	};

	void rut1();
	void null_function();

public:
	FSM();
	~FSM();

};

