#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif
#include "Global.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "Text.h"
#include "Timer.h"


#define FONT_SIZE				8
#define FONT_HEIGHT				(FONT_SIZE * 3 / 2)

#define TEXT_COLOR_BLACK		{ 0, 0, 0 }
#define TEXT_COLOR_GREY			{ 63, 63, 63 }
#define TEXT_COLOR_LIGHTGREY	{ 200, 200, 200 }
#define TEXT_COLOR_WHITE		{ 255, 255, 255 }
#define TEXT_COLOR_RED			{ 255, 50, 50 }

#define TEXT_BACKGROUND_BLACK	{ 0, 0, 0, 190 }
#define TEXT_BACKGROUND_GREEN	{ 30, 160, 30, 230 }


SDL_Surface *Text::charset = nullptr;
SDL_Surface *Text::screen = nullptr;
bool Text::blink = false;


static const struct {
	uint8_t height;
	const char *label;
	const char *legend;
} g_text_info[MAX_TEXT_INFO] = {
	/* TEXT_INFO_SCORES */ { 5, "SCORES", "up / down: scroll\np: sorted by points\nt: sorted by time\nenter: exit\nesc: quit" },
	/* TEXT_INFO_LOAD */ { 3, "LOAD GAME", "up / down: scroll\nenter: accept\nesc: quit" },
	/* TEXT_INFO_NEW */ { 5, NULL, "n: new game\n1..2: players\n3..5: select road\nl: load\nesc: quit" },
	/* TEXT_INFO_ONE_PLAYER */ { 8, NULL, "right / left: turn\nup: gas\ndown: brake/reverse\nspace: shooting\ns: save\np: pause/continue\nf: finish\nesc: quit" },
	/* TEXT_INFO_TWO_PLAYERS */ { 19, NULL,
	"---- PLAYER 1 ----\nright / left: turn\nup: gas\ndown: brake/reverse\nshift / ctrl left\n: shooting\n\n"
	"---- PLAYER 2 ----\na / d: turn\nw: gas\nx: brake/reverse\nshift / ctrl right\n: shooting\n\n"
	"space: shooting\ns: save\np: pause/continue\nf: finish\nesc: quit" },
	/* TEXT_INFO_END */ { 5, NULL, "n: new game\n1..2: players\nl: load\nenter: exit\nesc: quit" },
	/* TEXT_INFO_INSERT */ { 6, "INSERT", "-- ENTERED CHARS --\na..z 0..9\nspace dot\n\nenter: accept\nesc: quit" },
};




void Text::drawString(TextMode mode, SDL_Color color, uint16_t x, uint16_t y, const char* format, ...)
{
	static va_list ap;
	char buffer[512], *text = buffer;
	uint8_t scale = ((mode == TM_NORMAL_X2) || (mode == TM_SHADE_X2))? 2 : 1;
	SDL_Rect s, d;
	uint16_t x0 = x;

	va_start(ap, format);
	vsnprintf(buffer, sizeof(buffer), format, ap);
	buffer[sizeof(buffer) - 1] = '\0';
	va_end(ap);

	SDL_SetSurfaceColorMod(charset, color.r, color.g, color.b);
	s.w = FONT_SIZE;
	s.h = FONT_SIZE;
	d.w = FONT_SIZE * scale;
	d.h = FONT_SIZE * scale;
	while(*text) {
		if(*text == '\n') {
			if(mode == TM_COLON) {
				SDL_SetSurfaceColorMod(charset, color.r, color.g, color.b);
			}
			y += FONT_HEIGHT * scale;
			x = x0;
		} else {
			s.x = ((unsigned char)*text % 16) * FONT_SIZE;
			s.y = ((unsigned char)*text / 16) * FONT_SIZE;
			d.x = x;
			d.y = y;
			if(mode == TM_SHADE_X2) {
				SDL_Color temp = TEXT_COLOR_GREY;
				SDL_SetSurfaceColorMod(charset, temp.r, temp.g, temp.b);
				SDL_BlitScaled(charset, &s, screen, &d);
				SDL_SetSurfaceColorMod(charset, color.r, color.g, color.b);
				d.x = x - 1;
				d.y = y - 1;
			}
			SDL_BlitScaled(charset, &s, screen, &d);
			x += FONT_SIZE * scale;
			if((mode == TM_COLON) && (*text == ':')) {
				SDL_Color temp = TEXT_COLOR_LIGHTGREY;
				SDL_SetSurfaceColorMod(charset, temp.r, temp.g, temp.b);
			}
		}
		text++;
	}
}


void Text::drawRect(SDL_Renderer *renderer, SDL_Color color, SDL_Rect *rect)
{
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, rect);
	rect->x += FONT_SIZE;
	rect->y += FONT_SIZE;
	rect->h -= FONT_SIZE*2;
	rect->w -= FONT_SIZE*2;
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}


int Text::initialize(SDL_RWops *rwop)
{
	if(rwop && (charset = SDL_LoadBMP_RW(rwop, 1)) != nullptr) {
		SDL_SetColorKey(charset, true, 0x000000);
	} else {
		return -1;
	}
	return 0;
}


void Text::preUpdate(void)
{
	static class Timer g_timer(true);

	if(!g_timer.isRunning()) {
		g_timer.start();
	} if(g_timer.getTime() > GLOBAL_TIME_BLINK_MILISEK) {
		blink = !blink;
		g_timer.start();
	}
	screen = SDL_CreateRGBSurface(0, GLOBAL_WINDOW_WIDTH, GLOBAL_WINDOW_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
}


void Text::postUpdate(SDL_Renderer *renderer)
{
	SDL_Texture *score = SDL_CreateTextureFromSurface(renderer, screen);
	SDL_RenderCopy(renderer, score, NULL, NULL);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(score);
}


void Text::updateLegend(SDL_Renderer *renderer, enum TextInfoType type)
{
#if defined(GLOBAL_LEGEND_WIDTH) && (GLOBAL_LEGEND_WIDTH > 0)
#define MARGIN	16
	SDL_Rect rect = { GLOBAL_WINDOW_WIDTH - GLOBAL_LEGEND_WIDTH, MARGIN, GLOBAL_LEGEND_WIDTH - MARGIN, 52 };
	drawRect(renderer, TEXT_BACKGROUND_GREEN, &rect);
	drawString(TM_COLON, TEXT_COLOR_BLACK, rect.x, rect.y,
		"Pawel\n"
		"Pstragowski\n"
		"Album: s193473"
	);

#define HEIGHT(x)	(FONT_HEIGHT * (1 + x))
	rect = { GLOBAL_WINDOW_WIDTH - GLOBAL_LEGEND_WIDTH, GLOBAL_WINDOW_HEIGHT - MARGIN - 24 - HEIGHT(g_text_info[type % MAX_TEXT_INFO].height), GLOBAL_LEGEND_WIDTH - MARGIN, HEIGHT(g_text_info[type % MAX_TEXT_INFO].height) };
	drawRect(renderer, TEXT_BACKGROUND_GREEN, &rect);
	drawString(TM_COLON, TEXT_COLOR_BLACK, rect.x, rect.y, g_text_info[type % MAX_TEXT_INFO].legend);

	rect = { GLOBAL_WINDOW_WIDTH - GLOBAL_LEGEND_WIDTH, GLOBAL_WINDOW_HEIGHT - HEIGHT(1), GLOBAL_LEGEND_WIDTH - MARGIN, HEIGHT(1) };
	drawString(TM_NORMAL, TEXT_COLOR_BLACK, rect.x, rect.y, "abcdefg ghijklmno qr");

#endif /* defined(GLOBAL_LEGEND_WIDTH) && (GLOBAL_LEGEND_WIDTH > 0) */
}


void Text::updateRoad(SDL_Renderer *renderer, uint32_t timeSek, uint32_t fps, uint32_t distance)
{
	drawString(TM_SHADE_X2, TEXT_COLOR_WHITE, 32, 21, "%u:%02u.%02u", timeSek / 3600, (timeSek / 60) % 60, timeSek % 60);
	drawString(TM_NORMAL, TEXT_COLOR_WHITE, 32, 42, "fps: %u", fps);
	drawString(TM_NORMAL, TEXT_COLOR_WHITE, 32, 52, "distance: %d", distance / GLOBAL_ROAD_SPRITE_HEIGHT);
}


void Text::updatePlayer(SDL_Renderer *renderer, uint8_t no,
		uint32_t points, uint32_t lives, uint32_t shots,
		bool blinkPoints, bool blinkLives, bool blinkShots)
{
#define OFFSET	130
	SDL_Color color_player1 = TEXT_COLOR_WHITE;
	SDL_Color color_player2 = TEXT_COLOR_BLACK;
	uint16_t x = GLOBAL_WINDOW_WIDTH - GLOBAL_LEGEND_WIDTH - OFFSET * (1 + no);
	drawString(TM_NORMAL, (!no)? color_player1 : color_player2, x, 6, "PLAYER %u", no + 1);
	if(!blinkPoints || blink) {
		drawString(TM_SHADE_X2, (!no)? color_player1 : color_player2, x, 21, "%06u", points % 1000000);
	}
	if(!blinkLives || blink) {
		drawString(TM_NORMAL, (!no)? color_player1 : color_player2, x, 42, "lives: %u", lives);
	}
	if(!blinkShots || blink) {
		drawString(TM_NORMAL, (!no)? color_player1 : color_player2, x, 52, "shots: %u", shots);
	}
}


void Text::updateInfo(SDL_Renderer *renderer, const char *text)
{
	if(text && strlen(text) && blink) {
		drawString(TM_SHADE_X2, TEXT_COLOR_RED, (GLOBAL_WINDOW_WIDTH - (uint16_t)strlen(text) * FONT_SIZE * 2) / 2, GLOBAL_WINDOW_HEIGHT / 2 - FONT_SIZE, text);
	}
}


void Text::updateModal(SDL_Renderer *renderer, enum TextInfoType type, uint32_t index, Score::Node *node1, FileList::Node *node2)
{
#define TEXT_WIDTH		310
#define TEXT_HEIGHT		((TEXT_SCORES + 9) * FONT_HEIGHT)
#define TEXT_XP			((GLOBAL_WINDOW_WIDTH - TEXT_WIDTH) / 2)
#define TEXT_YP			((GLOBAL_WINDOW_HEIGHT - TEXT_HEIGHT) / 2)
	const char *label = g_text_info[type % MAX_TEXT_INFO].label;
	const char *name = g_text_info[type % MAX_TEXT_INFO].legend;
	uint16_t height = g_text_info[type % MAX_TEXT_INFO].height;

	SDL_Rect rect = {TEXT_XP, TEXT_YP, TEXT_WIDTH, TEXT_HEIGHT };
#if !defined(GLOBAL_LEGEND_WIDTH) && (GLOBAL_LEGEND_WIDTH > 0)
	rect.h = TEXT_HEIGHT + height * FONT_HEIGHT;
#endif /* !defined(GLOBAL_LEGEND_WIDTH) && (GLOBAL_LEGEND_WIDTH > 0) */
	drawRect(renderer, TEXT_BACKGROUND_BLACK, &rect);
	if(label) {
		drawString(TM_SHADE_X2, TEXT_COLOR_RED, TEXT_XP + (TEXT_WIDTH - (uint16_t)strlen(label) * FONT_SIZE * 2) / 2, TEXT_YP + 2 * FONT_HEIGHT, label);
	}
	drawString(TM_NORMAL, TEXT_COLOR_WHITE, TEXT_XP + (TEXT_WIDTH - 37 * FONT_SIZE) / 2, TEXT_YP + 5 * FONT_HEIGHT,
		((type == TEXT_INFO_SCORES) || (type == TEXT_INFO_INSERT))?
			"  RANK  POINTS  TIME       USER\n"
			" ----------------------------------- "
		:
			"\n"
			" ----------------------------------- "
	);

	if(node1 && ((type == TEXT_INFO_SCORES) || (type == TEXT_INFO_INSERT))) {
		for(uint8_t i=0; (i < TEXT_SCORES) && node1; i++) {
			drawString(TM_NORMAL, TEXT_COLOR_WHITE, TEXT_XP + (TEXT_WIDTH - 37 * FONT_SIZE) / 2, TEXT_YP + (7 + i) * FONT_HEIGHT,
				"  %4u  %6u  %3u:%02u.%02u  %-8s",
				(index + i + 1) % 10000,
				node1->data.points % 1000000,
				(node1->data.time / 3600) % 1000, (node1->data.time / 60) % 60, node1->data.time % 60,
				node1->data.user
			);
			node1 = (type == TEXT_INFO_SCORES)? node1->next : NULL;
		}
	} else if(node2 && (type == TEXT_INFO_LOAD)) {
		for(uint8_t i=0; (i < TEXT_SCORES) && node2; i++) {
			if((i != index) || blink) {
				drawString(TM_NORMAL, TEXT_COLOR_WHITE, TEXT_XP + (TEXT_WIDTH - 37 * FONT_SIZE) / 2, TEXT_YP + (7 + i) * FONT_HEIGHT,
					" %s",
					node2->filename
				);
			}
			node2 = node2->next;
		}
	}

#if !defined(GLOBAL_LEGEND_WIDTH) && (GLOBAL_LEGEND_WIDTH > 0)
	drawString(TM_NORMAL, TEXT_COLOR_WHITE, TEXT_XP + (TEXT_WIDTH - 37 * FONT_SIZE) / 2, TEXT_YP + (7 + TEXT_SCORES) * FONT_HEIGHT,
		" ----------------------------------- \n"
	);
	drawString(TM_NORMAL, TEXT_COLOR_WHITE, TEXT_XP + (TEXT_WIDTH - 37 * FONT_SIZE) / 2 + 2 * FONT_SIZE, TEXT_YP + (8 + TEXT_SCORES) * FONT_HEIGHT,
		g_text_info[TEXT_INFO_LOAD].legend
	);
#endif /* !defined(GLOBAL_LEGEND_WIDTH) && (GLOBAL_LEGEND_WIDTH > 0) */
}


void Text::deinitialize(void)
{
	if(charset != nullptr) {
		SDL_FreeSurface(charset);
	}
}
