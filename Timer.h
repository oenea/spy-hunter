#ifndef __TIMER_H__
#define __TIMER_H__

#include "SDL.h"


class Timer {
private:
	static class Timer *objects; /* Lista jednokierunkowa wszystkich timerów */
	class Timer *next; /* Dowiązanie do następnego timera */
	uint32_t timePause = 0; /* Zapamiętana wartość licznika na moment włączenia pauzy */
	bool pause = false; /* Aktywna pauza */
	bool free; /* Timer w trybie bez pauzowania */

	uint32_t timer = 0; /* Wartość zliczonego czasu timera */
	bool running = false; /* Uruchomiony timera */

public:
	static void startPause(void)
	{
		class Timer *object = objects;
		while(object) {
			if(!object->pause && !object->free) {
				object->timePause = object->getTime();
				object->pause = true;
			}
			object = object->next;
		}
	}

	static void stopPause(void)
	{
		class Timer *object = objects;
		while(object) {
			if(object->pause) {
				object->timer = SDL_GetTicks() - object->timePause;
				object->pause = false;
			}
			object = object->next;
		}
	}

	Timer(bool free = false)
	{
		next = objects;
		objects = this;

		this->free = free;
	}

	~Timer(void)
	{
		class Timer *object = objects;
		class Timer *prev = nullptr;

		while(object) {
			if(object == this) {
				if(prev != nullptr) {
					prev->next = object->next;
				} else {
					objects = object->next;
				}
				break;
			}
			prev = object;
			object = object->next;
		}
	}

	void start(void) { timer = SDL_GetTicks(); running = true; }
	void stop(void) { running = false; }
	int getTime(void) { return pause? timePause : (int)SDL_GetTicks() - timer; }
	bool isRunning(void) { return running; }
};


#endif /* __TIMER_H__ */
