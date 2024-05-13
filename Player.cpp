#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif
#include "Global.h"
#include <ctype.h>
#include <time.h>
#include "Player.h"
#include "Effect.h"
#include "Road.h"
#include "Text.h"
#include "Collision.h"


class Player *Player::objects = nullptr;
uint32_t Player::onePoints = 0;



int Player::getItem(uint32_t *index, enum PlayerNo *no, uint32_t *points, uint32_t *lives, uint32_t *shots, bool *halt, bool *immortality, bool *weapon)
{
	static class Player *g_object = objects;
	int result = -1;

	if(index) {
		result++;
		if(!*index) {
			g_object = objects;
		}
		if(g_object) {
			if(no) { *no = g_object->no; result++; }
			if(points) { *points = g_object->points; result++; }
			if(lives) { *lives = g_object->lives; result++; }
			if(shots) { *shots = g_object->shots; result++; }
			if(halt) { *halt = g_object->timerPoints.isRunning(); result++; }
			if(immortality) { *immortality = g_object->getImmortality(); result++; }
			if(weapon) { *weapon = g_object->timerWeapon.isRunning(); result++; }
			g_object = g_object->next;
			*index = *index + 1;
		}
	}
	return result;
}


bool Player::addPoints(enum CollisionType destroyer, enum VehicleType destroyerWhom)
{
	class Player *object = objects;

	/* Określenie do jakiego player-a należą punkty */
	while(object) {
		if(((object->no == PLAYER_1) && (
			(destroyer == COLLISION_PLAYER_1) ||
			(destroyer == COLLISION_PLAYER_1_BULLET) ||
			(destroyer == COLLISION_PLAYER_1_SHRAPNEL) ||
			(destroyer == COLLISION_PLAYER_1_ROCKET)
		)) || (object->no == PLAYER_2)) {
			/* Wstrzymanie naliczania punktów */
			if(destroyerWhom == VEHICLE_NON_ENEMY) {
				object->timerPoints.start();
			}
			if(!object->timerPoints.isRunning()) {
				if((destroyer == COLLISION_PLAYER_1_BULLET) || (destroyer == COLLISION_PLAYER_2_BULLET)) {
					object->points++;
				} else if((destroyer == COLLISION_PLAYER_1_SHRAPNEL) || (destroyer == COLLISION_PLAYER_2_SHRAPNEL)) {
					object->points+= 2;
				} else if((destroyer == COLLISION_PLAYER_1) || (destroyer == COLLISION_PLAYER_2)) {
					object->points+= 4;
				} else if((destroyer == COLLISION_PLAYER_1_ROCKET) || (destroyer == COLLISION_PLAYER_2_ROCKET)) {
					object->points+= 10;
				}
			}
			return true;
		}
		object = object->next;
	}
	return false;
}


void Player::render(SDL_Renderer *renderer, float periodInSekunds, float *velocityDistance)
{
	if(objects) {
		class Player *object = objects;
		class Player *objectDelete = nullptr;

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
}


void Player::clean(void)
{
	while(objects) {
		class Player *object = objects->next;
		delete objects;
		objects = object;
	}
}


Player::Player(enum PlayerNo no, enum VehicleModel model, uint32_t points, uint32_t lives, uint32_t shots) : Vehicle(
	(!no)? VEHICLE_PLAYER_1 : VEHICLE_PLAYER_2, model)
{
	/* Dodanie obiektu do listy jednokierunkowej */
	next = objects;
	objects = this;

	this->no = no;
	this->points = points;
	this->lives = lives;
	this->shots = shots;

	/* Pojazd Player 2 dodawany od lewej strony */
	if(no == PLAYER_2) setPosition(0, GLOBAL_VEHICLE_POSITION_Y);
}


Player::~Player()
{
	/* Usunięcie obiektu z listy jednokierunkowej */
	class Player *object = objects;
	class Player *prev = nullptr;

	onePoints = points;

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


void Player::update(SDL_Renderer *renderer, float periodInSekunds, float *velocityDistance)
{
	const uint8_t *keys = SDL_GetKeyboardState(NULL);
	bool right = ((!no)? (!keys[SDL_SCANCODE_LEFT] && keys[SDL_SCANCODE_RIGHT]) : (!keys[SDL_SCANCODE_A] && keys[SDL_SCANCODE_D]));
	bool left = ((!no)? (keys[SDL_SCANCODE_LEFT] && !keys[SDL_SCANCODE_RIGHT]) : (keys[SDL_SCANCODE_A] && !keys[SDL_SCANCODE_D]));
	bool gas = (keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W]);
	bool brake = (keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_X]);
	bool shot_bullet = ((!no)? keys[SDL_SCANCODE_RCTRL] : keys[SDL_SCANCODE_LCTRL]);
	bool shot_shrapnel = ((!no)? keys[SDL_SCANCODE_RSHIFT] : keys[SDL_SCANCODE_LSHIFT]) || keys[SDL_SCANCODE_SPACE];

	enum CollisionType destroyer;
	if(getDeleteMe(&destroyer, nullptr)) {
		if(lives > 0) {
			if(--lives) {
				setPosition(GLOBAL_VEHICLE_POSITION_X, GLOBAL_VEHICLE_POSITION_Y);
			} else {
				deleting = true;
			}
		}
	}

	/* Wstrzymanie licznika punktów */
	if(timerPoints.isRunning() && (timerPoints.getTime() > GLOBAL_TIME_STOP_POINTS_MILISEK)) {
		timerPoints.stop();
	}

	/* Wzmocnienie pojazdu */
	if(getWeapon()) {
		shots+= 100;
		timerWeapon.start();
	} else if(timerWeapon.isRunning() && (timerWeapon.getTime() > GLOBAL_TIME_WEAPON_MILISEK)) {
		timerWeapon.stop();
	}

	/* Wystrzelenie pocisku */
	float posx = getX();
	float posy = getY();
	if(shots && (shot_bullet || shot_shrapnel)) {
		if(!timerShot.isRunning()) {
			if(shot_bullet) {
				new Effect(EFFECT_BULLET, (no == PLAYER_1)? EFFECT_PLAYER_1 : EFFECT_PLAYER_2, (int16_t)posx + 15, (int16_t)posy - 24);
			} else if(shot_shrapnel) {
				/* Wzmocnienie rakietami przez 5sek. */
				if(timerWeapon.isRunning()) {
					new Effect(EFFECT_ROCKET, (no == PLAYER_1)? EFFECT_PLAYER_1 : EFFECT_PLAYER_2, (int16_t)posx + 15, (int16_t)posy - 34);
				} else {
					new Effect(EFFECT_SHRAPNEL, (no == PLAYER_1)? EFFECT_PLAYER_1 : EFFECT_PLAYER_2, (int16_t)posx + 15, (int16_t)posy - 34);
				}
			}
			shots--;
			timerShot.start();
		} else if(timerShot.getTime() > GLOBAL_TIME_PERIOD_SHOT_MILISEK) {
			timerShot.stop();
		}
	}

	float velocity = getVelocity(); /* Prędkość pojazdu */
	if(gas) {
		velocity += 1000.0f * periodInSekunds;
		if(velocity > 400.0f) velocity = 400.0f;

	} else if(brake) {
		velocity -= 1000.0f * periodInSekunds;
		if(velocity < -100.0f) velocity = -100.0f;

	} else {
		velocity -= 150.0f * periodInSekunds;
		if(velocity < 0.0f) velocity = 0.0f;
	}
	setVelocity(velocity);

	*velocityDistance = velocity * periodInSekunds;
	if(right) {
		posx+= *velocityDistance;
	} else if(left) {
		posx-= *velocityDistance;
	}
	setPosition(posx, posy);
}
