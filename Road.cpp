#include "Global.h"
#include <string.h>
#include "Road.h"
#include "RoadSpriteWide.cpp"
#include "RoadSpriteWide2.cpp"


SDL_Surface *Road::surface = nullptr;
SDL_Texture *Road::texture = nullptr;

RoadSpriteType *Road::lineArray = nullptr;
uint32_t Road::lineSize = 0;

Collision *Road::collision = nullptr;



void Road::addSegment(const RoadSpriteType *segment, uint32_t size)
{
	RoadSpriteType *arr = new RoadSpriteType[lineSize + size];

	if(lineArray != nullptr) {
		memcpy(&arr[0], lineArray, sizeof(RoadSpriteType) * lineSize);
		delete[] lineArray;
	}
	memcpy(&arr[lineSize], segment, sizeof(RoadSpriteType) * size);
	lineArray = arr;
	lineSize+= size;
}


void Road::select(enum RoadType type)
{
#define SEGMENT_PARAMS(x)	x, sizeof(x) / sizeof(x[0])
	clean();

	if(type == ROAD_WIDE) {
#if defined(GLOBAL_ROAD_WIDTH_IN_SPRITES) && (GLOBAL_ROAD_WIDTH_IN_SPRITES >= 20)
		addSegment( SEGMENT_PARAMS(segmentRoadWidestMeta) );
		for(uint8_t i=0; i < 32; i++) {
			addSegment( SEGMENT_PARAMS(segmentRoadWidest) );
		}
		addSegment( SEGMENT_PARAMS(segmentRoadWidestClose) );
		addSegment( SEGMENT_PARAMS(segmentRoadWide) );
		addSegment( SEGMENT_PARAMS(segmentRoadWide) );
		addSegment( SEGMENT_PARAMS(segmentRoadWidestOpen) );
		addSegment( SEGMENT_PARAMS(segmentRoadWidest) );
#endif /* defined(GLOBAL_ROAD_WIDTH_IN_SPRITES) && (GLOBAL_ROAD_WIDTH_IN_SPRITES >= 20) */

	} else if(type == ROAD_DOUBLE) {
#if defined(GLOBAL_ROAD_WIDTH_IN_SPRITES) && (GLOBAL_ROAD_WIDTH_IN_SPRITES >= 20)
		addSegment( SEGMENT_PARAMS(segmentRoadWidestDoubleMeta) );
		for(uint8_t i=0; i < 32; i++) {
			addSegment( SEGMENT_PARAMS(segmentRoadWidestDouble) );
		}
		addSegment( SEGMENT_PARAMS(segmentRoadWidestBifurcationClose) );
		addSegment( SEGMENT_PARAMS(segmentRoadWidest) );
		addSegment( SEGMENT_PARAMS(segmentRoadWidestBifurcationOpen) );
		addSegment( SEGMENT_PARAMS(segmentRoadWidestDouble) );
#endif /* defined(GLOBAL_ROAD_WIDTH_IN_SPRITES) && (GLOBAL_ROAD_WIDTH_IN_SPRITES >= 20) */

	} else { /* ROAD_BASIC */
#if defined(GLOBAL_ROAD_WIDTH_IN_SPRITES) && (GLOBAL_ROAD_WIDTH_IN_SPRITES >= 26)
		addSegment( SEGMENT_PARAMS(segmentBasicRoute1) );
		addSegment( SEGMENT_PARAMS(segmentBasicRoute2) );
#endif /* defined(GLOBAL_ROAD_WIDTH_IN_SPRITES) && (GLOBAL_ROAD_WIDTH_IN_SPRITES >= 26) */
	}

	if(!lineSize) {
		lineSize = GLOBAL_WINDOW_HEIGHT / GLOBAL_ROAD_SPRITE_HEIGHT;
		lineArray = new RoadSpriteType[lineSize];
		memset(lineArray, 0, sizeof(RoadSpriteType) * lineSize);
	}
}


/*!
	Inicjowanie statycznych zmiennych klasy
*/
int Road::initialize(SDL_Renderer *renderer, SDL_RWops *rwop)
{
	if(rwop && (surface = SDL_LoadBMP_RW(rwop, 1)) != nullptr) {
		if((texture = SDL_CreateTextureFromSurface(renderer, surface)) != nullptr) {
			select(ROAD_BASIC);

			if((collision = new Collision(COLLISION_ROAD)) != nullptr) {
				return 0;
			}
		}
	}
	return -1;
}


uint32_t Road::length(void)
{
	return (lineSize * GLOBAL_ROAD_SPRITE_HEIGHT);
}


/*!
	HEIGHT: 9
	y:			SCREEN		ARRAY[n]
--------------------------------------------------------
	0 * 64					s[8]	s[7]
	1 * 64		***			s[7]	s[6]
	2 * 64		***			s[6]	s[5]
	3 * 64		***			s[5]	s[4]
	4 * 64		***			s[4]	s[3]
	5 * 64		***			s[3]	s[2]
	6 * 64		***			s[2]	s[1]
	7 * 64		***			s[1]	s[0]
	8 * 64		***			s[0]	s[n-1]	offset: -64
*/
void Road::render(SDL_Renderer *renderer, uint32_t distance)
{
#define HEIGHT	((GLOBAL_WINDOW_HEIGHT / GLOBAL_ROAD_SPRITE_HEIGHT) + 1)
#define OFFSET	((int16_t)(-GLOBAL_ROAD_SPRITE_HEIGHT*3.5))

	/* Zapętlenie trasy */
	distance+= (OFFSET >= 0)? OFFSET : (lineSize * GLOBAL_ROAD_SPRITE_HEIGHT) + OFFSET;
	while(distance >= (lineSize * GLOBAL_ROAD_SPRITE_HEIGHT)) {
		distance-= (lineSize * GLOBAL_ROAD_SPRITE_HEIGHT);
	}

	if(texture != nullptr) {
		static SDL_Rect mask[HEIGHT * 3];
		uint8_t maskIndex = 0;

		for(uint8_t s = 0; s < HEIGHT; s++) {
			uint32_t idx = (distance / GLOBAL_ROAD_SPRITE_HEIGHT) + s;
			if(idx >= lineSize) {
				idx-= lineSize;
			}

			SDL_Rect rect;
			rect.y = ((HEIGHT - 2) - s) * GLOBAL_ROAD_SPRITE_HEIGHT + (distance % GLOBAL_ROAD_SPRITE_HEIGHT);

			/* Utworzenie obszarów do wykrywania kolizji z drogą (maksymalnie rozwidlenie dwóch dróg) */
			uint8_t no = 0;
			for(uint8_t i=0; i < GLOBAL_ROAD_WIDTH_IN_SPRITES; i++) {
				if((no == 0) && (lineArray[idx][i].mask != MASK_ALL)) {
						mask[maskIndex] = { 0, rect.y, (i + 1) * GLOBAL_ROAD_SPRITE_WIDTH - lineArray[idx][i].mask, GLOBAL_ROAD_SPRITE_HEIGHT };
						maskIndex++;
						no++;

				} else if(((no == 1) || (no == 3)) && (lineArray[idx][i].mask != MASK_NO)) {
					mask[maskIndex].x = i * GLOBAL_ROAD_SPRITE_WIDTH + ((lineArray[idx][i].mask == MASK_ALL)? 0 : -lineArray[idx][i].mask),
					mask[maskIndex].y = rect.y;
					mask[maskIndex].w = GLOBAL_WINDOW_WIDTH - mask[maskIndex].x;
					mask[maskIndex].h = GLOBAL_ROAD_SPRITE_HEIGHT;
					maskIndex++;
					no++;
				} else if((no == 2) && (lineArray[idx][i].mask != MASK_ALL)) {
					mask[maskIndex - 1].w = (i + 1) * GLOBAL_ROAD_SPRITE_WIDTH - lineArray[idx][i].mask - mask[maskIndex - 1].x;
					no++;
				}
			}

			/* Skopiowanie tekstury obrazujące widoczną cześć drogi */
			for(uint8_t i=0; i < GLOBAL_ROAD_WIDTH_IN_SPRITES; i++) {
				SDL_Rect section = { lineArray[idx][i].x, lineArray[idx][i].y, GLOBAL_ROAD_SPRITE_WIDTH, GLOBAL_ROAD_SPRITE_HEIGHT };
				rect.x = i * GLOBAL_ROAD_SPRITE_WIDTH;
				rect.w = section.w;
				rect.h = section.h;
				SDL_RenderCopy(renderer, texture, &section, &rect);
			}

			/* Linia mety */
			if(idx == 0) {
				SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
				SDL_SetRenderDrawColor(renderer, 127, 127, 127, 50);
				SDL_Rect fill = { 0, rect.y + GLOBAL_ROAD_SPRITE_HEIGHT - 5, GLOBAL_WINDOW_WIDTH, 3 };
				SDL_RenderFillRect(renderer, &fill);
				SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
			}
		}

		/* Odświeżenie mapy obszarów kolizji dla nowego widoku trasy */
		collision->setAreas(mask, maskIndex);
	}
}


void Road::clean(void)
{
	if(lineArray != nullptr) {
		delete[] lineArray;
		lineArray = nullptr;
		lineSize = 0;
	}
}


void Road::deinitialize(void)
{
	Road::clean();
	if(collision != nullptr) {
		delete collision;
	}
	if(texture != nullptr) {
		SDL_DestroyTexture(texture);
	}
	if(surface != nullptr) {
		SDL_FreeSurface(surface);
	}
}
