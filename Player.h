#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Global.h"
#include <stdlib.h>
#include "SDL.h"
#include "Vehicle.h"
#include "Timer.h"


enum PlayerNo {
	PLAYER_1,
	PLAYER_2
};


class Player : public Vehicle {
private:
	static class Player *objects; /* Lista jednokierunkowa obiektów danych gracza */
	static uint32_t onePoints;
	class Player *next;
	enum PlayerNo no;
	bool deleting = false;

	class Timer timerPoints; /* Timer wstrzymania licznika punktów gracza */
	class Timer timerWeapon; /* Timer trwania wzmocnienia gracza */
	class Timer timerShot; /* Timer odstępu pomiędzy wystrzałami gracza */
	uint32_t points;
	uint32_t lives;
	uint32_t shots;
	void update(SDL_Renderer *renderer, float periodInSekunds, float *velocityDistance);

public:
	static int getItem(uint32_t *index, enum PlayerNo *no, uint32_t *points, uint32_t *lives, uint32_t *shots, bool *halt, bool *immortality, bool *weapon);
	static bool addPoints(enum CollisionType destroyer, enum VehicleType destroyerWhom);
	static void render(SDL_Renderer *renderer, float periodInSekunds, float *velocityDistance);
	static void clean(void);
	static int16_t getOneVelocity(void) { return (objects)? (int16_t)objects->getVelocity() : 0; }
	static uint32_t getOnePoints(void) { return (objects)? objects->points : onePoints; }
	static bool isPresent(void) { return (objects != nullptr); }

	Player(enum PlayerNo no, enum VehicleModel model, uint32_t points = 0, uint32_t lives = 1, uint32_t shots = 100);
	~Player(void);
};


#endif /* __PLAYER_H__ */
