#ifndef __GLOBAL_H__
#define __GLOBAL_H__

//#define GLOBAL_COMPILE_BMP

//#define GLOBAL_SHOW_COLLISION


/* Liczba sprite'ów składająca się na szerokość drogi (oraz przestrzeń pod legendę) */
# define GLOBAL_ROAD_WIDTH_IN_SPRITES			26
# define GLOBAL_LEGEND_WIDTH_IN_SPRITES			7


/* Szerokość i długość sprite'a wycinka drogi */
#define GLOBAL_ROAD_SPRITE_WIDTH				32
#define GLOBAL_ROAD_SPRITE_HEIGHT				64
/* Szerokość i długość okna aplikacji (oraz przestrzeń pod legendę) */
#define GLOBAL_WINDOW_WIDTH						GLOBAL_ROAD_SPRITE_WIDTH * GLOBAL_ROAD_WIDTH_IN_SPRITES
#define GLOBAL_WINDOW_HEIGHT					GLOBAL_ROAD_SPRITE_HEIGHT * 10
#define GLOBAL_LEGEND_WIDTH						GLOBAL_LEGEND_WIDTH_IN_SPRITES * GLOBAL_ROAD_WIDTH_IN_SPRITES

/* Ustawienie początkowe pojazdu */
#define GLOBAL_VEHICLE_POSITION_X				(GLOBAL_WINDOW_WIDTH - GLOBAL_LEGEND_WIDTH)
#define GLOBAL_VEHICLE_POSITION_Y				(GLOBAL_WINDOW_HEIGHT / 2) + 100
/* Zakres utrzymywania pojazdów i efektów poza oknem w osi y */
#define GLOBAL_EXTENT_OUTSIDE_Y					500


/* Domyślne nazwy plików */
#define GLOBAL_PREFIX_FILENAME "spy-hunter"
#define GLOBAL_FILENAME_SCORE	GLOBAL_PREFIX_FILENAME".score"
#define GLOBAL_SUFIX_SAVED ".save"
/* Maksymalna liczba wyników zapisywana dp plików (posortowana po punktach) */
//#define GLOBAL_MAX_SCORES_TO_FILE				15


/* Maksymalna liczba obcych pojazdów */
#define GLOBAL_MAX_FOREIGN_VEHICLES				10

/* Szybkość migania tekstu */
#define GLOBAL_TIME_BLINK_MILISEK				250
/* Utrzymywanie powiadamiania na ekranie */
#define GLOBAL_TIME_NOTIFICATION_MILISEK		500

/* Odstęp pomiędzy pojawiającymi się nowymi pojazdamia na drodze */
#define GLOBAL_PERIOD_ADD_VEHICLE_MILISEK		2000
/* Odstęp pomiędzy pojawiającymi się efektmi na drodze */
#define GLOBAL_PERIOD_ADD_EFFECT_MILISEK		1000
/* Czas nieśmiertelności gracza na początku gry */
#define GLOBAL_TIME_IMMORTALITY_MILISEK			30000
/* Czas wstrzymania naliczania punktów */
#define GLOBAL_TIME_STOP_POINTS_MILISEK			10000
/* Czas trwania wzmocnienia */
#define GLOBAL_TIME_WEAPON_MILISEK				30000
/* Odstęp pomiędzy wystrzałami */
#define GLOBAL_TIME_PERIOD_SHOT_MILISEK			140
/* Czas od zakończenia do zaczęcia wpisywania rezultatu gry */
#define GLOBAL_TIME_GAMEOVER_TO_INSERT			3000


#endif /* __GLOBAL_H__ */
