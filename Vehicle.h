#ifndef __VEHICLE_H__
#define __VEHICLE_H__

#include "Global.h"
#include "SDL.h"
#include "Collision.h"
#include "Timer.h"


enum VehicleType {
	VEHICLE_PLAYER_1, /* Pojazd gracza nr 1 */
	VEHICLE_PLAYER_2, /* Pojazd gracza nr 2 */
	VEHICLE_ENEMY, /* Wrogi pojazd */
	VEHICLE_NON_ENEMY /* Nie-wrogi pojazd */
};


enum VehicleModel {
	VEHICLE_WHITE_CAR,
	VEHICLE_GREY_CAR,
	VEHICLE_RED_CAR,
	VEHICLE_BLUE_CAR,
	VEHICLE_MOTO,
	VEHICLE_WIDE_CAR,
	VEHICLE_WIDE_MCAR,
	VEHICLE_LONG_MCAR
};


enum VehicleMovement {
	VEHICLE_STRAIGHT,
	VEHICLE_GAS,
	VEHICLE_RIGHT,
	VEHICLE_LEFT
};


class Vehicle : public Collision {
private:
	static SDL_Surface *surface;
	static SDL_Texture *texture;
	static class Vehicle *objects; /* Lista jednokierunkowa obiektów */
	class Vehicle *next;
	bool deleteme = false;
	bool weapon = false; /* Wzmocnienie */

	enum VehicleType type;
	enum VehicleModel model;
	enum VehicleMovement movement;
	SDL_Rect collisionOffset, collisionArea;
	float x, y; /* Bieżąca pozycja pojazdu */
	float xLast, yLast; /* Ostatnia pozycja pojazdu */
	float velocity, velocityLast, velocitySlip; /* Prędkość pojazdu */
	class Timer timerPushing; /* Timer zepchnięcia z drogi */
	class Timer timerImmortality; /* Timer nieśmiertelności */
	class Timer timerSlip; /* Timer poślizgu */
	enum CollisionType destroyer; /* Typ kolizji powodującej zniszczenie pojazdu */
	enum VehicleType destroyerWhom; /* Rodzaj zniszczonego pojazdu */

	void setMovement(enum VehicleMovement movement) { x = (movement == VEHICLE_LEFT)? x - 2 : x + 2; }
	void update(SDL_Renderer *renderer, float periodInSekunds, float velocityDistance);

public:
	static int initialize(SDL_Renderer *renderer, SDL_RWops *rwop);
	static void render(SDL_Renderer *renderer, float periodInSekunds, float velocityDistance);
	static int getItem(uint32_t *index, enum VehicleType *type, enum VehicleModel *model, int16_t *x, int16_t *y, int16_t *velocity);
	static void deinitialize(void);

	Vehicle(enum VehicleType type, enum VehicleModel model, int16_t x = GLOBAL_VEHICLE_POSITION_X, int16_t y = GLOBAL_VEHICLE_POSITION_Y, int16_t velocity = 0);
	~Vehicle(void);
	bool detectCollision(enum CollisionType type, SDL_Rect *mine, SDL_Rect *foreign);
	void setPosition(float x, float y);
	enum VehicleType getType(void) { return this->type; }
	float getX(void) { return this->x; }
	float getY(void) { return this->y; }
	float getVelocity(void) { return this->velocity; }
	void setVelocity(float velocity) { this->velocity = velocity; }
	bool getDeleteMe(enum CollisionType *destroyer, enum VehicleType *whom) {
		if(destroyer){ *destroyer = this->destroyer; }
		if(whom){ *whom = this->destroyerWhom; }
		bool result = this->deleteme; this->deleteme = false; return result;
	}
	bool getWeapon(void) { bool result = this->weapon; this->weapon = false; return result; }
	bool getImmortality(void) { return timerImmortality.isRunning(); }
};


#endif /* __VEHICLE_H__ */