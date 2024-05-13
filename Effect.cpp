#include "Global.h"
#include "Collision.h"
#include "Effect.h"

#define STILE_SIZE	32


SDL_Surface *Effect::surface = nullptr;
SDL_Texture *Effect::texture = nullptr;
class Effect *Effect::objects = nullptr;



int Effect::initialize(SDL_Renderer *renderer, SDL_RWops *rwop)
{
	if(rwop && (surface = SDL_LoadBMP_RW(rwop, 1)) != nullptr) {
		if((texture = SDL_CreateTextureFromSurface(renderer, surface)) != nullptr) {
			return 0;
		}
	}
	return -1;
}


void Effect::render(SDL_Renderer *renderer, float periodInSekunds, float velocityDistance)
{
	class Effect *object = objects;
	class Effect *objectDelete = nullptr;

	while(object) {
		if(!object->deleting) {
			object->update(renderer, periodInSekunds, velocityDistance);
		} else {
			objectDelete = object;
		}
		object = object->next;
	}
	/* Usunięcie obiektu z listy i pamięci */
	if(objectDelete != nullptr) {
		delete objectDelete;
	}
}


int Effect::getItem(uint32_t *index, enum EffectType *type, enum EffectPlayer *player, int16_t *x, int16_t *y)
{
	static class Effect *g_object = objects;
	int result = -1;

	if(index) {
		result++;
		if(!*index) {
			g_object = objects;
		}
		if(g_object) {
			if(type) { *type = g_object->type; result++; }
			if(player) { *player = g_object->player; result++; }
			if(x) { *x = (int16_t)g_object->x; result++; }
			if(y) { *y = (int16_t)g_object->y; result++; }
			g_object = g_object->next;
			*index = *index + 1;
		}
	}
	return result;
}


void Effect::clean(void)
{
	while(objects) {
		class Effect *object = objects->next;
		delete objects;
		objects = object;
	}
}


void Effect::deinitialize(void)
{
	clean();

	if(texture != nullptr) {
		SDL_DestroyTexture(texture);
	}
	if(surface != nullptr) {
		SDL_FreeSurface(surface);
	}
}


Effect::Effect(enum EffectType type, enum EffectPlayer player, int16_t x, int16_t y, int16_t velocity): Collision(
	(type == EFFECT_BULLET)? ((player == EFFECT_PLAYER_1)? COLLISION_PLAYER_1_BULLET : (player == EFFECT_PLAYER_2)? COLLISION_PLAYER_2_BULLET : COLLISION_BULLET) :
	(type == EFFECT_SHRAPNEL)? ((player == EFFECT_PLAYER_1)? COLLISION_PLAYER_1_SHRAPNEL : (player == EFFECT_PLAYER_2)? COLLISION_PLAYER_2_SHRAPNEL : COLLISION_SHRAPNEL) :
	(type == EFFECT_ROCKET)? ((player == EFFECT_PLAYER_1)? COLLISION_PLAYER_1_ROCKET : (player == EFFECT_PLAYER_2)? COLLISION_PLAYER_2_ROCKET : COLLISION_ROCKET) :
	(type == EFFECT_BOMB)? COLLISION_BOMB :
	(type == EFFECT_OIL)? COLLISION_OIL :
	(type == EFFECT_PUDDLE)? COLLISION_PUDDLE :
	(type == EFFECT_ROAD_HOLE)? COLLISION_ROAD_HOLE :
	COLLISION_EFFECT, this)
{
	/* Dodanie obiektu do listy jednokierunkowej na końcu ze względu na renderowanie najpierw obiektów najstarszych */
	next = nullptr;
	if(objects) {
		class Effect *object = objects;
		while(object) {
			if(object->next == nullptr) {
				object->next = this;
				break;
			}
			object = object->next;
		}
	} else {
		objects = this;
	}

	this->type = type;
	this->player = player;
	this->x = x;
	this->y = y;
	this->collisionOffset = { 0, 0, 0, 0 };
	this->collisionArea = { 0, 0, 0, 0 };
	this->config = { 0, 0, 0, false, 0, 0 };

	if(type == EFFECT_BULLET) {
		this->collisionOffset = { 15, 11, STILE_SIZE-28, STILE_SIZE-21 };
		this->config = { 1, 2, 20, true, 800, 200 };

	} else if(type == EFFECT_SHRAPNEL) {
		this->collisionOffset = { 12, 11, STILE_SIZE-23, STILE_SIZE-11 };
		this->config = { 0, 1, 50, true, 700, 0 };

	} else if(type == EFFECT_ROCKET) {
		this->collisionOffset = { 12, 9, STILE_SIZE-24, STILE_SIZE-11 };
		this->config = { 0, 1, 20, true, 700, 0 };

	} else if((type == EFFECT_EXPLOTE_SHRAPNEL) || (type == EFFECT_EXPLOTE_BULLET)) {
		this->collisionOffset = { 0, 0, STILE_SIZE, STILE_SIZE };
		this->config = { 0, 5, 20, false, 0, 0 };

	} else if(type == EFFECT_RAZOR) {
		this->collisionOffset = { 0, 0, STILE_SIZE, STILE_SIZE };
		this->config = { 0, 3, 20, false, 0, 0 };

	} else if(type == EFFECT_BOMB) {
		this->collisionOffset = { 14, 0, STILE_SIZE-27, STILE_SIZE-9 };
		this->config = { 0, 1, 5, true, 0, 0 };

	} else if(type == EFFECT_OIL) {
		this->collisionOffset = { 0+8, 0+8, STILE_SIZE-8-8, STILE_SIZE-8-8-8 };
		this->config = { 1, 1, 0, true, 0, 0 };

	} else if((type == EFFECT_PUDDLE) || (type == EFFECT_PUDDLE_LEFT) || (type == EFFECT_PUDDLE_RIGHT)) {
		this->collisionOffset = { 0+5, 0+5, STILE_SIZE-5-5, STILE_SIZE-10-5-5 };
		if(type == EFFECT_PUDDLE_LEFT) {
			this->config = { 2, 2, 10, false, 0, 0 };
		} else if(type == EFFECT_PUDDLE_RIGHT) {
			this->config = { 3, 3, 10, false, 0, 0 };
		} else {
			this->config = { 0, 0, 0, true, 0, 0 };
		}
	} else if(type == EFFECT_ROAD_HOLE) {
		this->collisionOffset = { 9, 10, STILE_SIZE-17, STILE_SIZE-18 };
		this->config = { 5, 5, 0, true, 0, 0 };
	}

	if(velocity) {
		this->config.velocity = velocity;
	}
	this->frame = this->config.frameBegin;
}


Effect::~Effect()
{
	/* Usunięcie obiektu z listy jednokierunkowej */
	class Effect *object = objects;
	class Effect *prev = nullptr;

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


void Effect::update(SDL_Renderer *renderer, float periodInSekunds, float velocityDistance)
{
	y+= velocityDistance;

	if(this->config.velocity != 0) {
		y -= this->config.velocity * periodInSekunds;
	}
	if(this->config.frameSpeed > 0) {
		frame += this->config.frameSpeed * periodInSekunds;
		if((int)frame > this->config.frameEnd) {
			frame = (this->config.frameLoop)? this->config.frameBegin : this->config.frameEnd;
			finished = true;
			if(!this->config.frameLoop) {
				deleting = true;
			}
		}
	}
	if(this->config.time > 0) {
		if(!timer.isRunning()) {
			timer.start();
		} else if(timer.getTime() > (this->config.time + (int)(200.0f * velocityDistance))) {
			deleting = true;
		}
	}

	/* Oznaczenie obiektu do usunięcia gdy znajduje się poza oknem */
	if((y < -GLOBAL_EXTENT_OUTSIDE_Y) || (y > (GLOBAL_WINDOW_HEIGHT + GLOBAL_EXTENT_OUTSIDE_Y))) {
		deleting = true;
	}

	this->collisionArea = { (int)(x + collisionOffset.x), (int)(y + collisionOffset.y), collisionOffset.w, collisionOffset.h };
	setAreas(&this->collisionArea);

	uint8_t idx = type;
	if(type == EFFECT_SHRAPNEL) idx = EFFECT_BULLET;
	if((type == EFFECT_PUDDLE_LEFT) || (type == EFFECT_PUDDLE_RIGHT)) idx = EFFECT_PUDDLE;
	SDL_Rect section = { STILE_SIZE * (int)frame, STILE_SIZE * idx, STILE_SIZE, STILE_SIZE };
	SDL_Rect rect = { (int)x, (int)y, STILE_SIZE, STILE_SIZE };
	SDL_RenderCopy(renderer, texture, &section, &rect);
}


bool Effect::detectCollision(enum CollisionType type, SDL_Rect *mine, SDL_Rect *foreign)
{
	if(((type == COLLISION_ROAD) && (this->type != EFFECT_EXPLOTE_SHRAPNEL) && (this->type != EFFECT_EXPLOTE_BULLET) && (this->type != EFFECT_RAZOR)) ||
		((this->type == EFFECT_BULLET) && (type != COLLISION_BULLET) && (type != COLLISION_PLAYER_1_BULLET) && (type != COLLISION_PLAYER_2_BULLET) && (type != COLLISION_PUDDLE) && (type != COLLISION_OIL) && (type != COLLISION_ROAD_HOLE)) ||
		((this->type == EFFECT_SHRAPNEL) && (type != COLLISION_SHRAPNEL) && (type != COLLISION_PLAYER_1_SHRAPNEL) && (type != COLLISION_PLAYER_2_SHRAPNEL) && (type != COLLISION_PUDDLE) && (type != COLLISION_OIL) && (type != COLLISION_ROAD_HOLE)) ||
		((this->type == EFFECT_ROCKET) && (type != COLLISION_ROCKET) && (type != COLLISION_PLAYER_1_ROCKET) && (type != COLLISION_PLAYER_2_ROCKET) && (type != COLLISION_PUDDLE) && (type != COLLISION_OIL) && (type != COLLISION_ROAD_HOLE)) ||
		(this->type == EFFECT_BOMB) ||
		((this->type == EFFECT_PUDDLE) && ((type == COLLISION_PLAYER_1) || (type == COLLISION_PLAYER_2) || (type == COLLISION_VEHICLE_ENEMY) || (type == COLLISION_VEHICLE_NON_ENEMY) || (type == COLLISION_OIL))) ||
		((this->type == EFFECT_ROAD_HOLE) && ((type == COLLISION_PUDDLE) || (type == COLLISION_OIL)))
	) {
		deleting = true;
		return true;
	}
	return false;
}
