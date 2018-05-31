#include "EventManager.h"

#define MOVEMENT_FREQ 20.0

EventManager::EventManager(FuncionesGenerales * func, Feed * feed)
{
	add_lcd(func);
	add_feed(feed);

	if (al_init()){				
		if (al_install_keyboard()){
			ALLEGRO_TIMER * timer;
			ALLEGRO_EVENT_QUEUE * ev_queue;
			if ((ev_queue = al_create_event_queue()) && (timer = al_create_timer(1.0 / MOVEMENT_FREQ))) {
				this->timer = timer;
				queue = ev_queue;
				al_register_event_source(queue,al_get_keyboard_event_source());
				al_register_event_source(queue, al_get_timer_event_source(this->timer));
			}
			else {
				al_uninstall_keyboard();
				al_uninstall_system();
			}
		}
		else
		{
			std::cout<<"Error installing keyboard\n"<<std::endl;
			al_uninstall_system();
		}
	}
	else
	{
		fprintf(stderr, "Error initializing allegro system\n");
	}

}


EventManager::~EventManager()
{
}

//boolean that tells the user if there's a change in news and should call handle_event to get the new news.
bool EventManager::receive_event() {

	bool has_new_event = false;
	const News * news = NULL;

	ALLEGRO_EVENT ev;
	if (al_get_next_event(queue, &ev)) {
		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			move = true;			//move enables the keyboard input to be read.
		}
		else if ( (ev.type == ALLEGRO_EVENT_KEY_DOWN) && move)
		{
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_EQUALS:
				func->subir_vel();
				break;
			case ALLEGRO_KEY_MINUS:
				func->bajar_vel();
			case ALLEGRO_KEY_A:
				feed->get_previous_title();
				news = feed->get_previous_title();
				has_new_event = true;
				break;
			case ALLEGRO_KEY_R:
				news = feed->get_previous_title();
				has_new_event = true;
				
				break;
			case ALLEGRO_KEY_S:
				news = feed->get_next_title();
				has_new_event = true;
				break;
			case ALLEGRO_KEY_Q:
				should_quit = true;
				break;
			}
			move = false;
		}

	}	

	this->input_news = (News *)news;
	return has_new_event;
}

void EventManager::add_lcd(FuncionesGenerales * func) {
	this->func = func;
}

void EventManager::add_feed(Feed * feed) {
	this->feed = feed;
}

void EventManager::start_timer() {
	al_start_timer(timer);
}
bool EventManager::should_quit_now() {
	return should_quit;
}

const News * EventManager::handle_event() {
	return ((const News *)this->input_news);
}