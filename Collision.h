#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "SDL.h"


enum CollisionType {
	COLLISION_ROAD,
	COLLISION_VEHICLE_ENEMY,
	COLLISION_VEHICLE_NON_ENEMY,
	COLLISION_BULLET,
	COLLISION_SHRAPNEL,
	COLLISION_ROCKET,
	COLLISION_BOMB,
	COLLISION_OIL,
	COLLISION_PUDDLE,
	COLLISION_ROAD_HOLE,
	COLLISION_EFFECT,

	COLLISION_PLAYER_1,
	COLLISION_PLAYER_1_BULLET,
	COLLISION_PLAYER_1_SHRAPNEL,
	COLLISION_PLAYER_1_ROCKET,

	COLLISION_PLAYER_2,
	COLLISION_PLAYER_2_BULLET,
	COLLISION_PLAYER_2_SHRAPNEL,
	COLLISION_PLAYER_2_ROCKET
};


class Collision {
private:
	static class Collision *objects; /* Lista jednokierunkowa obiektów */
	class Collision *next;

	enum CollisionType type;
	Collision* callback;

	SDL_Rect *rectArray;
	uint8_t rectSize;

public:
	static void render(SDL_Renderer *renderer);
	static void check(void);

	Collision(CollisionType type, Collision *callback = nullptr);
	~Collision(void);

	void setAreas(SDL_Rect *rect, uint8_t size = 1);

	virtual bool detectCollision(enum CollisionType type, SDL_Rect *mine, SDL_Rect *foreign) {
		return false;
	}
};


#endif /* __COLLISION_H__ */
