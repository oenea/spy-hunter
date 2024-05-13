#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif
#include "Global.h"
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include "Scene.h"
#include "Player.h"
#include "Effect.h"
#include "Road.h"
#include "Text.h"
#include "Collision.h"


class Vehicle *Scene::vehicleList[GLOBAL_MAX_FOREIGN_VEHICLES];
class Timer *Timer::objects;

enum SceneState Scene::state = SCENE_INITIALIZE;
class Timer Scene::timerAddVehicle;
class Timer Scene::timerAddEffect;
class Timer Scene::timerEnemyShot;
class Timer Scene::timerSave;
class Timer Scene::timerGameOver;
float Scene::timeInSekunds = 0.0f;
float Scene::distance = 0.0f;
bool Scene::pause = false;
float Scene::velocityDistance = 0.0f;



void Scene::addVehicleList(void)
{
	for(uint8_t i=0; i < GLOBAL_MAX_FOREIGN_VEHICLES; i++) {
		if(vehicleList[i] == nullptr) {
			enum VehicleModel model = (enum VehicleModel)(VEHICLE_RED_CAR + getRand(VEHICLE_LONG_MCAR - VEHICLE_RED_CAR + 1));
			enum VehicleType type = VEHICLE_NON_ENEMY;
			int16_t velocity = (4 + getRand(15)) * 20;
			int16_t x = getRand(2)? (GLOBAL_WINDOW_WIDTH - GLOBAL_LEGEND_WIDTH)/ 3 : (GLOBAL_WINDOW_WIDTH - GLOBAL_LEGEND_WIDTH) * 2 / 3;
			int16_t y = (Player::getOneVelocity() >= velocity)? -64 : GLOBAL_WINDOW_HEIGHT; /* Czy pojazd ma się pojawić z góry */

			if((model == VEHICLE_WIDE_CAR) || (model == VEHICLE_WIDE_MCAR) || (model == VEHICLE_LONG_MCAR)) {
				type = VEHICLE_ENEMY;
			}
			vehicleList[i] = new Vehicle(type, model, x, y, velocity);
			break;
		}
	}
}


void Scene::updateVehicleList(void)
{
	enum CollisionType destroyer;
	enum VehicleType destroyerWhom;

	for(uint8_t i=0; i < GLOBAL_MAX_FOREIGN_VEHICLES; i++) {
		if(vehicleList[i] != nullptr) {
			if(((int)vehicleList[i]->getY() < -GLOBAL_EXTENT_OUTSIDE_Y) || ((int)vehicleList[i]->getY() > GLOBAL_WINDOW_HEIGHT + GLOBAL_EXTENT_OUTSIDE_Y)) {
				delete vehicleList[i];
				vehicleList[i] = nullptr;

			} else if(vehicleList[i]->getDeleteMe(&destroyer, &destroyerWhom)) {
				Player::addPoints(destroyer, destroyerWhom);
				delete vehicleList[i];
				vehicleList[i] = nullptr;

			} else if(vehicleList[i]->getType() == VEHICLE_ENEMY) {
				if(!timerEnemyShot.isRunning()) {
					if(!getRand(10)) {
						new Effect(EFFECT_SHRAPNEL, EFFECT_PLAYER_NONE, (int)vehicleList[i]->getX() + 15, (int)vehicleList[i]->getY() - 24 - 8, (int)vehicleList[i]->getVelocity() + 200);
					}
					timerEnemyShot.start();
				} else if(timerEnemyShot.getTime() > GLOBAL_TIME_PERIOD_SHOT_MILISEK * 4) {
					timerEnemyShot.stop();
				}
			}
		}
	}
}


void Scene::deleteAllVehicleList(void)
{
	for(uint8_t i=0; i < GLOBAL_MAX_FOREIGN_VEHICLES; i++) {
		if(vehicleList[i] != nullptr) {
			delete vehicleList[i];
			vehicleList[i] = nullptr;
		}
	}
}


int Scene::initialize(SDL_Renderer *renderer)
{
	SDL_RWops *rwop;
	int result = 0;

//#if !defined(GLOBAL_SHOW_COLLISION)
# if defined(GLOBAL_COMPILE_BMP)
#  include "sf_road.bmp.h"
	rwop = SDL_RWFromConstMem(src____sf_road_bmp, sizeof(src____sf_road_bmp));
# else /* !defined(GLOBAL_COMPILE_BMP) */
	rwop = SDL_RWFromFile("sf_road.bmp", "rb");
# endif /* !defined(GLOBAL_COMPILE_BMP) */

//#else /* defined(GLOBAL_SHOW_COLLISION) */
//# if defined(GLOBAL_COMPILE_BMP)
//#  include "sf_road_debug.bmp.h"
//	rwop = SDL_RWFromConstMem(src____sf_road_debug_bmp, sizeof(src____sf_road_debug_bmp));
//# else /* !defined(GLOBAL_COMPILE_BMP) */
//	rwop = SDL_RWFromFile("sf_road_debug.bmp", "rb");
//# endif /* !defined(GLOBAL_COMPILE_BMP) */
//#endif /* defined(GLOBAL_SHOW_COLLISION) */
	if(result >= 0) result = Road::initialize(renderer, rwop);

#if defined(GLOBAL_COMPILE_BMP)
# include "sf_cs8x8.bmp.h"
	rwop = SDL_RWFromConstMem(src____sf_cs8x8_bmp, sizeof(src____sf_cs8x8_bmp));
#else /* !defined(GLOBAL_COMPILE_BMP) */
	rwop = SDL_RWFromFile("sf_cs8x8.bmp", "rb");
#endif /* !defined(GLOBAL_COMPILE_BMP) */
	if(result >= 0) result = Text::initialize(rwop);

#if defined(GLOBAL_COMPILE_BMP)
# include "sf_vehicles.bmp.h"
	rwop = SDL_RWFromConstMem(src____sf_vehicles_bmp, sizeof(src____sf_vehicles_bmp));
#else /* !defined(GLOBAL_COMPILE_BMP) */
	rwop = SDL_RWFromFile("sf_vehicles.bmp", "rb");
#endif /* !defined(GLOBAL_COMPILE_BMP) */
	if(result >= 0) result = Vehicle::initialize(renderer, rwop);

#if defined(GLOBAL_COMPILE_BMP)
# include "sf_effects.bmp.h"
	rwop = SDL_RWFromConstMem(src____sf_effects_bmp, sizeof(src____sf_effects_bmp));
#else /* !defined(GLOBAL_COMPILE_BMP) */
	rwop = SDL_RWFromFile("sf_effects.bmp", "rb");
#endif /* !defined(GLOBAL_COMPILE_BMP) */
	if(result >= 0) result = Effect::initialize(renderer, rwop);

	return result;
}


void Scene::renderTextByState(SDL_Renderer *renderer, float periodInSekunds, int finalfps, SDL_Keycode keycode)
{
	static uint32_t g_index = 0;

	if(state == SCENE_INITIALIZE) {
		if(Score::load(GLOBAL_FILENAME_SCORE) < 0) {
			Score::defaults();
		}
		g_index = 0;
		state = SCENE_SCORES;

	} else if(state == SCENE_SCORES) {
		Text::updateLegend(renderer, TEXT_INFO_SCORES);
		Text::updateModal(renderer, TEXT_INFO_SCORES, g_index, Score::getList(g_index));

		velocityDistance = 100 * periodInSekunds;

		/* Zmiana sortowania wyników */
		if(keycode == SDLK_p) {
			Score::sortByPoints();
			g_index = 0;
		} else if(keycode == SDLK_t) {
			Score::sortByTime();
			g_index = 0;
		} else if((keycode == SDLK_DOWN) && ((g_index + TEXT_SCORES) < Score::getSize())) {
			g_index++;
		} else if((keycode == SDLK_UP) && (g_index > 0)) {
			g_index--;
		} else if((keycode == SDLK_RETURN)) {
			state = SCENE_PLAYER_NEW;
		}
	} else if(state == SCENE_LOAD) {
		static class FileList *g_list = nullptr;

		Text::updateLegend(renderer, TEXT_INFO_LOAD);

		if(g_list == nullptr) {
			g_list = new FileList(GLOBAL_SUFIX_SAVED);

		} else {
			Text::updateModal(renderer, TEXT_INFO_LOAD, g_index, g_list->getList(0));

			if((keycode == SDLK_DOWN) && ((g_index/* + TEXT_SCORES*/) < g_list->getSize())) {
				g_index++;

			} else if((keycode == SDLK_UP) && (g_index > 0)) {
				g_index--;

			} else if((keycode == SDLK_RETURN) || (keycode == SDLK_ESCAPE)) {
				FileList::Node *node = g_list->getList(g_index);
				int result;
				if(node && ((result = load(node->filename)) > 0)) {
					state = (result == 1)? SCENE_PLAYER_ONE : SCENE_PLAYER_TWO;
				} else {
					state = SCENE_PLAYER_NEW;
				}
				delete g_list;
				g_list = nullptr;
			}
		}
	} else if(state == SCENE_PLAYER_NEW) {
player_new:
		Text::updateLegend(renderer, TEXT_INFO_NEW);
		Text::updateRoad(renderer, (uint32_t)timeInSekunds, finalfps, (uint32_t)distance);
		Text::updateInfo(renderer, "START NEW GAME");

		/* Nowa gra z jednym lub dwoma graczami */
		if((keycode == SDLK_n) || (keycode == SDLK_1) || (keycode == SDLK_2)) {
			deleteAllVehicleList();
			Player::clean();

			new Player(PLAYER_1, VEHICLE_WHITE_CAR);
			state = SCENE_PLAYER_ONE;

			if(keycode == SDLK_2) {
				new Player(PLAYER_2, VEHICLE_GREY_CAR);
				state = SCENE_PLAYER_TWO;
			}
			timeInSekunds = 0;
			distance = 0;
		} else if((keycode == SDLK_l)) {
			g_index = 0;
			state = SCENE_LOAD;
		}
#if 1
		if((keycode >= SDLK_3) && (keycode <= SDLK_5)) {
			Road::select((keycode == SDLK_3)? ROAD_BASIC : (keycode == SDLK_4)? ROAD_WIDE : ROAD_DOUBLE );
		}
#endif

	} else if((state == SCENE_PLAYER_ONE) || (state == SCENE_PLAYER_TWO)) {
		Text::updateLegend(renderer, (state == SCENE_PLAYER_ONE)? TEXT_INFO_ONE_PLAYER : TEXT_INFO_TWO_PLAYERS);
		if(Player::isPresent()) {
			Text::updateRoad(renderer, (uint32_t)timeInSekunds, finalfps, (uint32_t)distance);

			timeInSekunds += periodInSekunds;

			if(timerSave.isRunning()) {
				Text::updateInfo(renderer, "SAVE");
				if(timerSave.getTime() > GLOBAL_TIME_NOTIFICATION_MILISEK) {
					timerSave.stop();
				}
			} else if(pause) {
				Text::updateInfo(renderer, "PAUSE");
			}

			uint32_t index = 0;
			enum PlayerNo noPlayer;
			uint32_t points, lives, shots;
			bool halt, immortality, weapon;
			while(Player::getItem(&index, &noPlayer, &points, &lives, &shots, &halt, &immortality, &weapon) == 7) {
				Text::updatePlayer(renderer, noPlayer, points, lives, shots, halt, immortality, weapon);
			}

			if(keycode == SDLK_p) {
				/* Wstrzymanie i wznowienie gry */
				pause = !pause;
			} else if(keycode == SDLK_s) {
				/* Zapis stanu gry */
				save();
				timerSave.start();
			} else if(keycode == SDLK_f) {
				Player::clean();
			}
		} else {
			keycode = SDLK_f;
		}
		if(keycode == SDLK_f) {
			/* Zakończenie gry */
			velocityDistance = 0.0f;
			timerGameOver.start();
			state = SCENE_PLAYER_END;
		}
	} else if(state == SCENE_PLAYER_END) {
		Text::updateLegend(renderer, TEXT_INFO_END);
		Text::updateInfo(renderer, "GAME OVER");

		if((keycode == SDLK_n) || (keycode == SDLK_l) || (keycode == SDLK_1) || (keycode == SDLK_2)) {
			goto player_new;

		} else if(keycode == SDLK_RETURN) {
			timerGameOver.stop();
			g_index = 0;
			state = SCENE_PLAYER_NEW;

		} else if(!timerGameOver.isRunning() || (timerGameOver.getTime() > GLOBAL_TIME_GAMEOVER_TO_INSERT)) {
			timerGameOver.stop();
			Score::addToList(Score::Data { Player::getOnePoints(), (uint32_t)timeInSekunds, SCORE_MAGIC_USER });
			Score::findByUser(SCORE_MAGIC_USER, &g_index);
			state = SCENE_INSERT;
		}

	} else if(state == SCENE_INSERT) {
		Text::updateLegend(renderer, TEXT_INFO_INSERT);

		Score::Node *node = Score::getList(g_index);

		if(node) {
			Text::updateModal(renderer, TEXT_INFO_INSERT, g_index, node);

			static uint8_t g_text_index = 0;
			char *string = node->data.user;
			uint8_t size = sizeof(node->data.user);
			if((keycode >= 'a') && (keycode <= 'z') || (keycode >= '0') && (keycode <= '9') || (keycode == ' ') || (keycode == '.')) {
				if(g_text_index < (size - 1)) {
					string[g_text_index++] = toupper(keycode);
				}
			} else if(keycode == SDLK_BACKSPACE) {
				if(g_text_index > 0) {
					string[g_text_index--] = ' ';
				}
			}
			if((keycode != SDLK_RETURN) && (keycode != SDLK_ESCAPE)) {
				if(g_text_index < (size - 1)) {
					string[g_text_index] = Text::getBlink()? TEXT_CODE_CHAR_CURSOR : ' ';
				}
				string[g_text_index + 1] = '\0';
			} else {
				string[g_text_index] = '\0';
				g_text_index = 0;
			}
		} else {
			keycode = SDLK_RETURN;
		}
		if(keycode == SDLK_RETURN) {
			g_index = 0;
			state = SCENE_SCORES;
		}
	}
}


bool Scene::render(SDL_Renderer *renderer, float periodInSekunds, int finalfps)
{
	SDL_Event event;
	SDL_PollEvent(&event);
	SDL_Keycode keycode = (event.type == SDL_KEYDOWN)? event.key.keysym.sym : SDLK_UNKNOWN;

	if(!pause) {
#if defined(GLOBAL_PERIOD_ADD_VEHICLE_MILISEK)
		/* Tworzenie i renderowanie innych pojazdów na drodze */
		if(!timerAddVehicle.isRunning()) {
			addVehicleList();
			timerAddVehicle.start();
		} else if(timerAddVehicle.getTime() > GLOBAL_PERIOD_ADD_VEHICLE_MILISEK) {
			timerAddVehicle.stop();
		}
		updateVehicleList();
#endif /* defined(GLOBAL_PERIOD_ADD_VEHICLE_MILISEK) */

#if defined(GLOBAL_PERIOD_ADD_EFFECT_MILISEK)
		if(!timerAddEffect.isRunning()) {
			if(velocityDistance > 0.0f) {
				int16_t x1 = 32 + getRand(GLOBAL_WINDOW_WIDTH - 64);
				int16_t x2 = 32 + getRand(GLOBAL_WINDOW_WIDTH - 64);
				int16_t y1 = 32 - getRand(GLOBAL_EXTENT_OUTSIDE_Y);
				int16_t y2 = 32 - getRand(GLOBAL_EXTENT_OUTSIDE_Y);

				if(!getRand(3)) {
					new Effect(EFFECT_PUDDLE, EFFECT_PLAYER_NONE, x1, y1);
				} else if(!getRand(4)) {
					int16_t x = 32 + getRand(GLOBAL_WINDOW_WIDTH - 64);
					new Effect(EFFECT_BOMB, EFFECT_PLAYER_NONE, x1, y1);
					new Effect(EFFECT_BOMB, EFFECT_PLAYER_NONE, x1+10, y1);
				}
				if(!getRand(3)) {
					int16_t x = 32 + getRand(GLOBAL_WINDOW_WIDTH - 64);
					new Effect(EFFECT_OIL, EFFECT_PLAYER_NONE, x2, y2);
				} else if(!getRand(2)) {
					int16_t x = 32 + getRand(GLOBAL_WINDOW_WIDTH - 64);
					new Effect(EFFECT_ROAD_HOLE, EFFECT_PLAYER_NONE, x2, y2);
				}
			}
			timerAddEffect.start();
		} else if(timerAddEffect.getTime() > GLOBAL_PERIOD_ADD_EFFECT_MILISEK) {
			timerAddEffect.stop();
		}
#endif /* defined(GLOBAL_PERIOD_ADD_EFFECT_MILISEK) */
		Timer::stopPause();

	} else {
		Timer::startPause();
		periodInSekunds = 0;
	}

	distance+= velocityDistance;
	if((distance < 0) || (distance > Road::length())) {
		distance = 0;
	}

	Player::render(renderer, periodInSekunds, &velocityDistance);
	Road::render(renderer, (uint32_t)distance);
	Effect::render(renderer, periodInSekunds, velocityDistance);
	Vehicle::render(renderer, periodInSekunds, velocityDistance);
#if defined(GLOBAL_SHOW_COLLISION)
	Collision::render(renderer);
#endif /* defined(GLOBAL_SHOW_COLLISION) */
	Collision::check();

	/* Renderowanie tekstu musi być na końcu łańcuszka */
	Text::preUpdate();
	renderTextByState(renderer, periodInSekunds, finalfps, keycode);
	Text::postUpdate(renderer);

	return ((event.type == SDL_QUIT) || (keycode == SDLK_ESCAPE));
}


int Scene::save(void)
{
	char filename[MAX_FILENAME_SIZE];
	time_t t = time(0);
	struct tm *now = localtime(&t);
	FILE *file;

	if(strftime(filename, sizeof(filename), GLOBAL_PREFIX_FILENAME "-%Y%m%d_%H%m%S" GLOBAL_SUFIX_SAVED, now) > 0) {
		if((file = fopen(filename, "wt")) != NULL) {
			enum PlayerNo noPlayer;
			enum VehicleType typeVehicle;
			enum VehicleModel modelVehicle;
			enum EffectType typeEffect;
			enum EffectPlayer playerEffect;
			uint32_t index, points, lives, shots;
			int16_t x, y, velocity;
			uint8_t players = 0;
			uint8_t vehicles = 0;
			uint8_t effects = 0;

			fprintf(file, "global: timeInSekunds(%u) distance(%u)\n", (uint32_t)timeInSekunds, (uint32_t)distance / GLOBAL_ROAD_SPRITE_HEIGHT);

			index = 0;
			while(Player::getItem(&index, &noPlayer, &points, &lives, &shots, nullptr, nullptr, nullptr) == 4) {
				fprintf(file, "player %u: points(%u) lives(%u) shots(%u)\n", noPlayer + 1, points, lives, shots);
				players++;
			}

			index = 0;
			while(Vehicle::getItem(&index, &typeVehicle, &modelVehicle, &x, &y, &velocity) == 5) {
				if((typeVehicle == VEHICLE_ENEMY) || (typeVehicle == VEHICLE_NON_ENEMY)) {
					fprintf(file, "vehicle %u: type(%u) model(%u) x(%d) y(%d) velocity(%d)\n", vehicles + 1, typeVehicle, modelVehicle, x, y, velocity);
					vehicles++;
				}
			}
			index = 0;
			while(Effect::getItem(&index, &typeEffect, &playerEffect, &x, &y) == 4) {
				if((typeEffect == EFFECT_OIL) || (typeEffect == EFFECT_PUDDLE) || (typeEffect == EFFECT_ROAD_HOLE) || (typeEffect == EFFECT_BOMB)) {
					fprintf(file, "effect %u: type(%u) player(%u) x(%d) y(%d)\n", effects + 1, typeEffect, playerEffect, x, y);
					effects++;
				}
			}
			fclose(file);
			return 0;
		}
	}
	return -1;
}


int Scene::load(const char *filename)
{
#define MAX_LINE_LENGTH	128
	FILE *file;
	char line[MAX_LINE_LENGTH];

	if((file = fopen(filename, "rt")) != NULL) {
		uint8_t players = 0;
		uint8_t vehicles = 0;
		uint8_t vehiclesForeign = 0;
		uint8_t effects = 0;

		deleteAllVehicleList();
		Player::clean();
		Effect::clean();

		while(fgets(line, MAX_LINE_LENGTH, file) != NULL) {
			unsigned int timeInSekunds, distance, points, lives, shots, no, type, model, player;
			int x, y, velocity;

			if(sscanf(line, "global: timeInSekunds(%u) distance(%u)", &timeInSekunds, &distance) == 2) {
				Scene::timeInSekunds = (float)timeInSekunds;
				Scene::distance = (float)distance * GLOBAL_ROAD_SPRITE_HEIGHT;
			} else if(sscanf(line, "player %u: points(%u) lives(%u) shots(%u)", &no, &points, &lives, &shots) == 4) {
				if((no >= 1) && (no <= 2)) {
					class Player *object = new Player((no == 1)? PLAYER_1 : PLAYER_2, (no == 1)? VEHICLE_WHITE_CAR : VEHICLE_GREY_CAR, points, lives, shots);
					players++;
				}
			} else if(sscanf(line, "vehicle %u: type(%u) model(%u) x(%d) y(%d) velocity(%d)", &no, &type, &model, &x, &y, &velocity) == 6) {
				if(((enum VehicleType)type == VEHICLE_ENEMY) || ((enum VehicleType)type == VEHICLE_NON_ENEMY)) {
					vehicleList[vehiclesForeign] = new Vehicle((enum VehicleType)type, (enum VehicleModel)model, x, y, velocity);
					vehiclesForeign++;
				}
				vehicles++;
			} else if(sscanf(line, "effect %u: type(%u) player(%u) x(%d) y(%d)", &no, &type, &player, &x, &y) == 5) {
				new Effect((enum EffectType)type, (enum EffectPlayer)player, x, y);
				effects++;
			}
		}
		fclose(file);
		return players;
	}
	return -1;
}


void Scene::deinitialize(void)
{
	deleteAllVehicleList();
	Score::save(GLOBAL_FILENAME_SCORE);
	Score::freeList();
	Player::deinitialize();
	Effect::deinitialize();
	Vehicle::deinitialize();
	Text::deinitialize();
	Road::deinitialize();
}
