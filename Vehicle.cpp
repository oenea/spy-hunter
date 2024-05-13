#include "Global.h"
#include "Collision.h"
#include "Vehicle.h"
#include "Effect.h"

#define MTILE_SIZE	64



SDL_Surface *Vehicle::surface = nullptr;
SDL_Texture *Vehicle::texture = nullptr;
class Vehicle *Vehicle::objects = nullptr;



int Vehicle::initialize(SDL_Renderer *renderer, SDL_RWops *rwop)
{
	if(rwop && (surface = SDL_LoadBMP_RW(rwop, 1)) != nullptr) {
		if((texture = SDL_CreateTextureFromSurface(renderer, surface)) != nullptr) {
			return 0;
		}
	}
	return -1;
}


void Vehicle::render(SDL_Renderer *renderer, float periodInSekunds, float velocityDistance)
{
	class Vehicle *object = objects;

	while(object) {
		object->update(renderer, periodInSekunds, velocityDistance);
		object = object->next;
	}
}


int Vehicle::getItem(uint32_t *index, enum VehicleType *type, enum VehicleModel *model, int16_t *x, int16_t *y, int16_t *velocity)
{
	static class Vehicle *g_object = objects;
	int result = -1;

	if(index) {
		result++;
		if(!*index) {
			g_object = objects;
		}
		if(g_object) {
			if(type) { *type = g_object->type; result++; }
			if(model) { *model = g_object->model; result++; }
			if(x) { *x = (int16_t)g_object->x; result++; }
			if(y) { *y = (int16_t)g_object->y; result++; }
			if(velocity) { *velocity = (int16_t)g_object->velocity; result++; }
			g_object = g_object->next;
			*index = *index + 1;
		}
	}
	return result;
}


void Vehicle::deinitialize(void)
{
	while(objects) {
		class Vehicle *object = objects->next;
		delete objects;
		objects = object;
	}

	if(texture != nullptr) {
		SDL_DestroyTexture(texture);
	}
	if(surface != nullptr) {
		SDL_FreeSurface(surface);
	}
}


Vehicle::Vehicle(enum VehicleType type, enum VehicleModel model, int16_t x, int16_t y, int16_t velocity) : Collision(
	(type == VEHICLE_PLAYER_1)? COLLISION_PLAYER_1 :
	(type == VEHICLE_PLAYER_2)? COLLISION_PLAYER_2 :
	(type == VEHICLE_ENEMY)? COLLISION_VEHICLE_ENEMY :
	COLLISION_VEHICLE_NON_ENEMY, this)
{
	/* Dodanie obiektu do listy jednokierunkowej */
	next = objects;
	objects = this;

	this->type = type;
	this->model = model;
	this->x = x;
	this->y = y;
	this->velocity = velocity;
	if(((type == VEHICLE_PLAYER_1) || (type == VEHICLE_PLAYER_2))) {
		timerImmortality.start();
	}

	if((model == VEHICLE_WHITE_CAR) || (model == VEHICLE_GREY_CAR)) {
		this->collisionOffset = { 21, 0, 24, 41 };

	} else if(model == VEHICLE_RED_CAR) {
		this->collisionOffset = { 20, 0, 25, 40 };

	} else if(model == VEHICLE_BLUE_CAR) {
		this->collisionOffset = { 20, 0, 23, 32 };

	} else if(model == VEHICLE_MOTO) {
		this->collisionOffset = { 23, 0, 19, 32 };

	} else if(model == VEHICLE_WIDE_CAR) {
		this->collisionOffset = { 18, 0, 28, 41 };

	} else if(model == VEHICLE_WIDE_MCAR) {
		this->collisionOffset = { 19, 0, 24, 41 };

	} else if(model == VEHICLE_LONG_MCAR) {
		this->collisionOffset = { 17, 0, 28, 58 };
	}
}


Vehicle::~Vehicle()
{
	/* Usunięcie obiektu z listy jednokierunkowej */
	class Vehicle *object = objects;
	class Vehicle *prev = nullptr;

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


void Vehicle::setPosition(float x, float y)
{
	this->x = x;
	this->y = y;

	/* Ograniczenie położenia w poziomie do szerokości okna */
	if((int)this->x > GLOBAL_WINDOW_WIDTH - (this->collisionOffset.x + this->collisionOffset.w)) {
		this->x = (float)GLOBAL_WINDOW_WIDTH - (this->collisionOffset.x + this->collisionOffset.w);
	}
	if((int)this->x < -this->collisionOffset.x) {
		this->x = (float)-this->collisionOffset.x;
	}
}


void Vehicle::update(SDL_Renderer *renderer, float periodInSekunds, float velocityDistance)
{
	/* Nieśmiertelność */
	if(timerImmortality.isRunning() && (timerImmortality.getTime() > GLOBAL_TIME_IMMORTALITY_MILISEK)) {
		timerImmortality.stop();
	}

	/* Zmiana położenia uwzględniająca prędkość pojazdu */
	y-= this->velocity * periodInSekunds - velocityDistance;

	/* Poślizg */
	if(timerSlip.isRunning() && (timerSlip.getTime() > 50)) {
		this->velocity = this->velocitySlip;
		timerSlip.stop();
	}

	/* Obrazowanie przyspieszania i skręcania pojazdu */
	movement = VEHICLE_STRAIGHT;
	if(((int)velocity > 0) && (velocityLast <= velocity) && ((type == VEHICLE_PLAYER_1) || (type == VEHICLE_PLAYER_2))) {
		movement = VEHICLE_GAS;
	}
	if(xLast < x) {
		movement = VEHICLE_RIGHT;
	} else if(xLast > x) {
		movement = VEHICLE_LEFT;
	}
	xLast = x; yLast = y;
	velocityLast = velocity;

	SDL_Rect section = { MTILE_SIZE * movement, MTILE_SIZE * model, MTILE_SIZE, MTILE_SIZE };
	SDL_Rect rect = { (int)x, (int)y, MTILE_SIZE, MTILE_SIZE };

	this->collisionArea = { (int)(x + collisionOffset.x), (int)(y + collisionOffset.y), collisionOffset.w, collisionOffset.h };
	setAreas(&this->collisionArea);
	SDL_RenderCopy(renderer, texture, &section, &rect);
}


bool Vehicle::detectCollision(enum CollisionType type, SDL_Rect *mine, SDL_Rect *foreign)
{
	bool result = false;

	if((type == COLLISION_PLAYER_1) || (type == COLLISION_PLAYER_2) || (type == COLLISION_VEHICLE_ENEMY) || (type == COLLISION_VEHICLE_NON_ENEMY)) {
		if(mine->x >= foreign->x) {
			setMovement(VEHICLE_RIGHT);
		} else {
			setMovement(VEHICLE_LEFT);
		}
		result = true;

	} else if(type == COLLISION_ROAD) {
		if((mine->x <= (foreign->x +foreign->w)) && (!foreign->x || ((mine->x + mine->w) > (foreign->x + foreign->w)))){
			setMovement(VEHICLE_RIGHT);
		} else {
			setMovement(VEHICLE_LEFT);
		}
		result = true;

	} else if((type == COLLISION_PLAYER_1_BULLET) || (type == COLLISION_PLAYER_1_SHRAPNEL) || (type == COLLISION_PLAYER_1_ROCKET) ||
		(type == COLLISION_PLAYER_2_BULLET) || (type == COLLISION_PLAYER_2_SHRAPNEL) || (type == COLLISION_PLAYER_2_ROCKET) ||
		(type == COLLISION_BULLET) || (type == COLLISION_SHRAPNEL) || (type == COLLISION_ROCKET)) {
		/* Eksplozja gdy czubek pocisku dotknie pojazdu */
		if(!timerImmortality.isRunning()) {
			if((mine->y + mine->h > foreign->y) && (mine->y + mine->h < foreign->y + foreign->y)) {
				enum EffectType effect = ((type == COLLISION_PLAYER_1_BULLET) || (type == COLLISION_PLAYER_2_BULLET) || (type == COLLISION_BULLET))? EFFECT_EXPLOTE_BULLET : EFFECT_EXPLOTE_SHRAPNEL;
				new Effect(effect, EFFECT_PLAYER_NONE, mine->x, mine->y);
				this->destroyer = type;
				this->destroyerWhom = this->type;
				this->deleteme = true;
			}
		}
		result = true;

	} else if(type == COLLISION_BOMB) {
		/* Przechwycenie bomby (wzmocnienie) */
		this->weapon = true;
		result = true;

	} else if(type == COLLISION_OIL) {
		if(!timerSlip.isRunning()) {
			this->velocitySlip = this->velocity;
			this->velocity+= 40;
			timerSlip.start();
		}
		result = true;

	} else if(type == COLLISION_PUDDLE) {
		if((mine->x + mine->w / 2) < (foreign->x + foreign->w / 2)) {
			new Effect(EFFECT_PUDDLE_RIGHT, EFFECT_PLAYER_NONE, mine->x + mine->w - 2, mine->y - 10);
		} else {
			new Effect(EFFECT_PUDDLE_LEFT, EFFECT_PLAYER_NONE, mine->x - foreign->w + 2, mine->y - 10);
		}
		result = true;

	} else if(type == COLLISION_ROAD_HOLE) {
		/* Najechanie pojazdu na dziurę */
		if(!timerImmortality.isRunning()) {
			new Effect(EFFECT_RAZOR, EFFECT_PLAYER_NONE, mine->x, mine->y - foreign->h);
			this->destroyer = type;
			this->destroyerWhom = this->type;
			this->deleteme = true;
		}
		result = true;
	}

	/* Wykrycie zepchnięcia obcego pojazdu z drogi */
	if((this->type != VEHICLE_PLAYER_1) && (this->type != VEHICLE_PLAYER_2)) {
		if((type == COLLISION_PLAYER_1) || (type == COLLISION_PLAYER_2) || (type == COLLISION_VEHICLE_ENEMY) || (type == COLLISION_VEHICLE_NON_ENEMY)) {
			/* Włączania odliczania czasu od ostatniej kolizji pojazdu (nie gracza) */
			this->destroyer = type;
			this->destroyerWhom = this->type;
			timerPushing.start();
		} else if(type == COLLISION_ROAD) {
			if(timerPushing.isRunning() && (timerPushing.getTime() < 100)) {
				if(!timerImmortality.isRunning()) {
					new Effect(EFFECT_RAZOR, EFFECT_PLAYER_NONE, mine->x, mine->y);
					this->deleteme = true;
				}
			} else {
				timerPushing.stop();
			}
		}
	}
	return result;
}
