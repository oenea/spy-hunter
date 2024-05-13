#ifndef __ROAD_H__
#define __ROAD_H__

#include "Global.h"
#include "SDL.h"
#include "Collision.h"


typedef struct {
	uint16_t x;
	uint16_t y;
	int16_t mask;
} RoadSpriteType[GLOBAL_ROAD_WIDTH_IN_SPRITES];



enum RoadType {
	ROAD_BASIC,
	ROAD_WIDE,
	ROAD_DOUBLE
};



class Road {
private:
	static SDL_Surface *surface;
	static SDL_Texture *texture;
	static RoadSpriteType *lineArray; /* Tablica sprite'ów całej trasy */
	static uint32_t lineSize; /* Długość trasy w powyższej tablicy */
	static Collision *collision;

	static void addSegment(const RoadSpriteType *segment, uint32_t size);
	static void clean(void);

public:
	static int initialize(SDL_Renderer *renderer, SDL_RWops *rwop);
	static void select(enum RoadType type);
	static uint32_t length(void);
	static void render(SDL_Renderer *renderer, uint32_t distance);
	static void deinitialize(void);
};


#endif /* __ROAD_H__ */
