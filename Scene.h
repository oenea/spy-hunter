#ifndef __SCENE_H__
#define __SCENE_H__

#include "Global.h"
#include <stdlib.h>
#include "SDL.h"
#include "Vehicle.h"
#include "Timer.h"


enum SceneState {
	SCENE_INITIALIZE, /* Inicjalizacja */
	SCENE_SCORES, /* Prezentacja wszystkich wyników */
	SCENE_LOAD, /* Wczytanie zapisanego stanu gry (selekcja pliku) */
	SCENE_PLAYER_NEW,	/* Oczekiwanie na nową grę */
	SCENE_PLAYER_ONE,	/* Gra z jednym graczem */
	SCENE_PLAYER_TWO,	/* Gra z dwoma graczami */
	SCENE_PLAYER_END,	/* Koniec gry */
	SCENE_INSERT /* Wstawienie wyniku na listę zwycięzców */
};


class Scene {
private:
	static class Vehicle *vehicleList[GLOBAL_MAX_FOREIGN_VEHICLES]; /* Lista aktywnych pojazdów */
	static void addVehicleList(void);
	static void updateVehicleList(void);
	static void deleteAllVehicleList(void);
	static void renderTextByState(SDL_Renderer *renderer, float periodInSekunds, int finalfps, SDL_Keycode keycode);

	static enum SceneState state;
	static class Timer timerAddVehicle; /* Timer tworzenia nowych pojazdów na drodze */
	static class Timer timerAddEffect; /* Timer tworzenia efektów na drodze */
	static class Timer timerEnemyShot; /* Timer odstępu pomiędzy wystrzałami wroga */
	static class Timer timerSave; /* Timer powiadamiania o zapisie gry */
	static class Timer timerGameOver; /* Timer komunikatu zakończenia gry */
	static float timeInSekunds; /* Czas gry */
	static float velocityDistance; /* Szybkość przesuwania drogi */
	static float distance; /* Dystans pokonanej drogi */
	static bool pause; /* Wstrzymanie gry */

public:
	static int initialize(SDL_Renderer *renderer);
	static bool render(SDL_Renderer *renderer, float periodInSekunds, int finalfps);
	static int save(void);
	static int load(const char *filename);
	static void deinitialize(void);

	static int getRand(int range) { srand(SDL_GetTicks()); return (rand() % range); }
};


#endif /* __SCENE_H__ */
