#ifndef __TEXT_H__
#define __TEXT_H__

#include "Global.h"
#include "SDL.h"
#include "Score.h"
#include "FileList.h"


#define TEXT_SCORES 			20
#define TEXT_CODE_CHAR_CURSOR	(16*13 + 11)



enum TextInfoType {
	TEXT_INFO_SCORES,
	TEXT_INFO_LOAD,
	TEXT_INFO_NEW,
	TEXT_INFO_ONE_PLAYER,
	TEXT_INFO_TWO_PLAYERS,
	TEXT_INFO_END,
	TEXT_INFO_INSERT,
	MAX_TEXT_INFO
};


class Text {
private:
	static SDL_Surface *charset;
	static SDL_Surface *screen;

	typedef enum {
		TM_NORMAL = 0,
		TM_COLON,
		TM_NORMAL_X2,
		TM_SHADE_X2,
	} TextMode;
	static void drawString(TextMode mode, SDL_Color color, uint16_t x, uint16_t y, const char* format, ...);
	static void drawRect(SDL_Renderer *renderer, SDL_Color color, SDL_Rect *rect);
	static void updateModal(SDL_Renderer *renderer, enum TextInfoType type, uint32_t index, Score::Node *node1, FileList::Node *node2);

	static bool blink;

public:
	static int initialize(SDL_RWops *rwop);
	static void deinitialize(void);

	static void preUpdate(void);
	static void updateLegend(SDL_Renderer *renderer, enum TextInfoType type);
	static void updateRoad(SDL_Renderer *renderer, uint32_t timeSek, uint32_t fps, uint32_t distance);
	static void updatePlayer(SDL_Renderer *renderer, uint8_t no,
		uint32_t points, uint32_t lives, uint32_t shots,
		bool blinkPoints = false, bool blinkLives = false, bool blinkShots = false);
	static void updateInfo(SDL_Renderer *renderer, const char *text);
	static void updateModal(SDL_Renderer *renderer, enum TextInfoType type, uint32_t index, Score::Node *node) { updateModal(renderer, type, index, node, NULL); }
	static void updateModal(SDL_Renderer *renderer, enum TextInfoType type, uint32_t index, FileList::Node *node) { updateModal(renderer, type, index, NULL, node); }
	static void postUpdate(SDL_Renderer *renderer);
	static bool getBlink(void) { return blink; }
};


#endif /* __TEXT_H__ */
