#include "Global.h"
#include "Collision.h"


class Collision *Collision::objects = nullptr;



void Collision::render(SDL_Renderer *renderer)
{
	class Collision *object = objects;
	uint8_t alpha = 80;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	while(object) {
		SDL_SetRenderDrawColor(renderer, 0, 255, 255, alpha);
		for(uint8_t i=0; i < object->rectSize; i++) {
			SDL_RenderFillRect(renderer, &object->rectArray[i]);
		}
		object = object->next;
	}
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}


void Collision::check(void)
{
	class Collision *objectA = objects;

	while(objectA) {
		class Collision *objectB = objects;

		while(objectB) {
			if(objectA != objectB) {
				for(uint8_t i=0; i < objectB->rectSize; i++) {
					if(SDL_HasIntersection(&objectA->rectArray[0], &objectB->rectArray[i])) {
						if(objectA->callback) {
							objectA->callback->detectCollision(objectB->type, &objectA->rectArray[0], &objectB->rectArray[i]);
						}
					}
				}
			}
			objectB = objectB->next;
		}
		objectA = objectA->next;
	}
}



Collision::Collision(CollisionType type, Collision *callback)
{
	/* Dodanie obiektu do listy jednokierunkowej */
	next = objects;
	objects = this;

	this->type = type;
	this->callback = callback;
	this->rectSize = 0;
}


Collision::~Collision()
{
	/* Usunięcie obiektu z listy jednokierunkowej */
	class Collision *object = objects;
	class Collision *prev = nullptr;

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


void Collision::setAreas(SDL_Rect *rect, uint8_t size)
{
	this->rectArray = rect;
	this->rectSize = size;
}
