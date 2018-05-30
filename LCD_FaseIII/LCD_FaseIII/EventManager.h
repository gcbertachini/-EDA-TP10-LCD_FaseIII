#pragma once
#include <iostream>
#include <allegro5/allegro5.h> 
#include "Archivos nuevos\FuncionesGenerales.h"
#include "Feed.h"

class EventManager
{
public:
	EventManager(FuncionesGenerales * func, Feed * feed);
	~EventManager();

	bool receive_event();
	const News  * handle_event();

	void start_timer();
	bool should_quit_now();

private :

	News * input_news;

	FuncionesGenerales * func;
	Feed * feed;

	ALLEGRO_EVENT_QUEUE * queue;
	ALLEGRO_TIMER * timer;

	void add_lcd(FuncionesGenerales * func);
	void add_feed(Feed * feed);


	bool move;					//booleano de cuando debo manejar el input

	bool should_quit;


};



