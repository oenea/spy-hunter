#ifndef __EFFECT_H__
#define __EFFECT_H__

#include "SDL.h"
#include "Collision.h"
#include "Timer.h"


enum EffectType {
	EFFECT_BULLET,
	EFFECT_OIL,
	EFFECT_SPRAY,
	EFFECT_ROCKET,
	EFFECT_BOMB,
	EFFECT_EXPLOTE_SHRAPNEL,
	EFFECT_EXPLOTE_BULLET,
	EFFECT_RAZOR,
	EFFECT_PUDDLE,
	EFFECT_ROAD_HOLE,

	EFFECT_SHRAPNEL,
	EFFECT_PUDDLE_LEFT,
	EFFECT_PUDDLE_RIGHT
};


enum EffectPlayer {
	EFFECT_PLAYER_NONE,
	EFFECT_PLAYER_1,
	EFFECT_PLAYER_2
};


class Effect : public Collision {
private:
	typedef struct {
		uint8_t frameBegin; /* Indeks pierwszego sprite'a animacji */
		uint8_t frameEnd; /* Indeks ostatniego sprite'a animacji */
		uint16_t frameSpeed; /* Szybkość animacji */
		bool frameLoop; /* Włączenie zapętlenia animacji */
		int16_t velocity; /* Szybkość przemieszczania */
		uint16_t time; /* Czas do zakończenia */
	} EffectConfig;

	static SDL_Surface *surface;
	static SDL_Texture *texture;
	static class Effect *objects; /* Lista jednokierunkowa obiektów (odwrócona) */
	class Effect *next;
	bool deleting = false;
	bool finished = false;
	float x, y;
	float frame;
	class Timer timer;

	enum EffectType type;
	enum EffectPlayer player; /* Wymagane do odtworzenia obiektu (właściciela - gracza) */
	SDL_Rect collisionOffset, collisionArea;
	EffectConfig config;

	void update(SDL_Renderer *renderer, float periodInSekunds, float velocityDistance);

public:
	static int initialize(SDL_Renderer *renderer, SDL_RWops *rwop);
	static void render(SDL_Renderer *renderer, float periodInSekunds, float velocityDistance);
	static int getItem(uint32_t *index, enum EffectType *type, enum EffectPlayer *player, int16_t *x, int16_t *y);
	static void clean(void);
	static void deinitialize(void);

	Effect(enum EffectType type, enum EffectPlayer player = EFFECT_PLAYER_NONE, int16_t x = GLOBAL_VEHICLE_POSITION_X, int16_t y = GLOBAL_VEHICLE_POSITION_Y, int16_t velocity = 0);
	~Effect(void);
	bool getFinished(void) { return finished; }
	bool detectCollision(enum CollisionType type, SDL_Rect *mine, SDL_Rect *foreign);
};


#endif /* __EFFECT_H__ */
