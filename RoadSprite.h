#ifndef __ROAD_SPRITE_H__
#define __ROAD_SPRITE_H__

#include "Global.h"

#define MASK_ALL		0
#define MASK_NO			GLOBAL_ROAD_SPRITE_WIDTH
#define MASK_LEFT(x)	(x)
#define MASK_RIGHT(x)	-(x)


/* Green Tiles */
#define T_GRASS____		{ 0 * GLOBAL_ROAD_SPRITE_WIDTH, 0 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_BUSH___A1		{ 1 * GLOBAL_ROAD_SPRITE_WIDTH, 0 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_BUSH___A2		{ 2 * GLOBAL_ROAD_SPRITE_WIDTH, 0 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_BUSH___B1		{ 3 * GLOBAL_ROAD_SPRITE_WIDTH, 0 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_BUSH___B2		{ 4 * GLOBAL_ROAD_SPRITE_WIDTH, 0 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_TREE___A1		{ 5 * GLOBAL_ROAD_SPRITE_WIDTH, 0 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_TREE___A2		{ 6 * GLOBAL_ROAD_SPRITE_WIDTH, 0 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_TREE___B1		{ 7 * GLOBAL_ROAD_SPRITE_WIDTH, 0 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_TREE___B2		{ 8 * GLOBAL_ROAD_SPRITE_WIDTH, 0 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_TREE___C1		{ 9 * GLOBAL_ROAD_SPRITE_WIDTH, 0 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_TREE___C2		{ 10 * GLOBAL_ROAD_SPRITE_WIDTH, 0 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_TREE___D1		{ 11 * GLOBAL_ROAD_SPRITE_WIDTH, 0 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_TREE___D2		{ 12 * GLOBAL_ROAD_SPRITE_WIDTH, 0 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_TREE___E1		{ 13 * GLOBAL_ROAD_SPRITE_WIDTH, 0 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_TREE___E2		{ 14 * GLOBAL_ROAD_SPRITE_WIDTH, 0 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }

/* Rect Tiles */
#define T_ROAD_____		{ 0 * GLOBAL_ROAD_SPRITE_WIDTH, 1 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_NO }
//#define T_SAND_____	{ 1 * GLOBAL_ROAD_SPRITE_WIDTH, 1 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_RECT___A1		{ 2 * GLOBAL_ROAD_SPRITE_WIDTH, 1 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_LEFT(4) }
#define T_RECT___A2		{ 3 * GLOBAL_ROAD_SPRITE_WIDTH, 1 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_RIGHT(4) }
#define T_RECT___B1		{ 4 * GLOBAL_ROAD_SPRITE_WIDTH, 1 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_LEFT(4) }
#define T_RECT___B2		{ 5 * GLOBAL_ROAD_SPRITE_WIDTH, 1 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_RIGHT(4) }

/* Road Minus Tiles */
#define T_RMINUS_A1		{ 0 * GLOBAL_ROAD_SPRITE_WIDTH, 2 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_LEFT(8) }
#define T_RMINUS_A2		{ 1 * GLOBAL_ROAD_SPRITE_WIDTH, 2 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_RIGHT(8) }
#define T_RMINUS_B1		{ 2 * GLOBAL_ROAD_SPRITE_WIDTH, 2 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_LEFT(12) }
#define T_RMINUS_B2		{ 3 * GLOBAL_ROAD_SPRITE_WIDTH, 2 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_RIGHT(12) }
#define T_RMINUS_C1		{ 4 * GLOBAL_ROAD_SPRITE_WIDTH, 2 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_LEFT(20) }
#define T_RMINUS_C2		{ 5 * GLOBAL_ROAD_SPRITE_WIDTH, 2 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_RIGHT(20) }
#define T_RMINUS_D1		{ 6 * GLOBAL_ROAD_SPRITE_WIDTH, 2 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_LEFT(24) }
#define T_RMINUS_D2		{ 7 * GLOBAL_ROAD_SPRITE_WIDTH, 2 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_RIGHT(24) }
#define T_RMINUS_E1		{ 8 * GLOBAL_ROAD_SPRITE_WIDTH, 2 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_LEFT(26) }
#define T_RMINUS_E2		{ 9 * GLOBAL_ROAD_SPRITE_WIDTH, 2 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_RIGHT(26) }
#define T_RMINUS_F1		{ 10 * GLOBAL_ROAD_SPRITE_WIDTH, 2 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_LEFT(28) }
#define T_RMINUS_F2		{ 11 * GLOBAL_ROAD_SPRITE_WIDTH, 2 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_RIGHT(28) }
#define T_RMINUS_G1		{ 12 * GLOBAL_ROAD_SPRITE_WIDTH, 2 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_LEFT(32) }
#define T_RMINUS_G2		{ 13 * GLOBAL_ROAD_SPRITE_WIDTH, 2 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_RIGHT(32) }

/* Grass Minus Tiles */
//#define T_GMINUS_A1	{ 0 * GLOBAL_ROAD_SPRITE_WIDTH, 3 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
//#define T_GMINUS_A2	{ 1 * GLOBAL_ROAD_SPRITE_WIDTH, 3 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_GMINUS_B1		{ 2 * GLOBAL_ROAD_SPRITE_WIDTH, 3 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_GMINUS_B2		{ 3 * GLOBAL_ROAD_SPRITE_WIDTH, 3 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_GMINUS_C1		{ 4 * GLOBAL_ROAD_SPRITE_WIDTH, 3 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_GMINUS_C2		{ 5 * GLOBAL_ROAD_SPRITE_WIDTH, 3 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_GMINUS_D1		{ 6 * GLOBAL_ROAD_SPRITE_WIDTH, 3 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_GMINUS_D2		{ 7 * GLOBAL_ROAD_SPRITE_WIDTH, 3 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_GMINUS_E1		{ 8 * GLOBAL_ROAD_SPRITE_WIDTH, 3 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_GMINUS_E2		{ 9 * GLOBAL_ROAD_SPRITE_WIDTH, 3 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_GMINUS_F1		{ 10 * GLOBAL_ROAD_SPRITE_WIDTH, 3 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_GMINUS_F2		{ 11 * GLOBAL_ROAD_SPRITE_WIDTH, 3 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_GMINUS_G1		{ 12 * GLOBAL_ROAD_SPRITE_WIDTH, 3 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_GMINUS_G2		{ 13 * GLOBAL_ROAD_SPRITE_WIDTH, 3 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }

/* Curves Tiles (tiles horizontal x tiles vertical) */

/* Road	Curve Left 2 x 1 */
#define T_RCURL2_A1		{ 0 * GLOBAL_ROAD_SPRITE_WIDTH, 4 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_LEFT(24) }
#define T_RCURL2_A2		{ 1 * GLOBAL_ROAD_SPRITE_WIDTH, 4 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_RIGHT(MASK_NO - 24) }
#define T_RCURL2_B1		{ 2 * GLOBAL_ROAD_SPRITE_WIDTH, 4 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_LEFT(8) }
#define T_RCURL2_B2		{ 3 * GLOBAL_ROAD_SPRITE_WIDTH, 4 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_RIGHT(MASK_NO - 8) }
/* Road	Curve Right 2 x 1 */
#define T_RCURR2_A1		{ 4 * GLOBAL_ROAD_SPRITE_WIDTH, 4 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_LEFT(8) }
#define T_RCURR2_A2		{ 5 * GLOBAL_ROAD_SPRITE_WIDTH, 4 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_RIGHT(MASK_NO - 8) }
#define T_RCURR2_B1		{ 6 * GLOBAL_ROAD_SPRITE_WIDTH, 4 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_LEFT(24) }
#define T_RCURR2_B2		{ 7 * GLOBAL_ROAD_SPRITE_WIDTH, 4 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_RIGHT(MASK_NO - 24) }
/* Road	Curve Right 3 x 1 */
#define T_RCURR3_A1		{ 8 * GLOBAL_ROAD_SPRITE_WIDTH, 4 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_LEFT(8) }
#define T_RCURR3_A2		{ 9 * GLOBAL_ROAD_SPRITE_WIDTH, 4 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_RIGHT(MASK_NO - 8) }
#define T_RCURR3_B1		{ 10 * GLOBAL_ROAD_SPRITE_WIDTH, 4 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_LEFT(16) }
#define T_RCURR3_B2		{ 11 * GLOBAL_ROAD_SPRITE_WIDTH, 4 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_RIGHT(MASK_NO - 16) }
#define T_RCURR3_C1		{ 12 * GLOBAL_ROAD_SPRITE_WIDTH, 4 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_LEFT(24) }
#define T_RCURR3_C2		{ 13 * GLOBAL_ROAD_SPRITE_WIDTH, 4 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_RIGHT(MASK_NO - 24) }
/* Road	Curve Left 3 x 1 */
#define T_RCURL3_A1		{ 14 * GLOBAL_ROAD_SPRITE_WIDTH, 4 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_LEFT(24) }
#define T_RCURL3_A2		{ 15 * GLOBAL_ROAD_SPRITE_WIDTH, 4 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_RIGHT(MASK_NO - 24) }
#define T_RCURL3_B1		{ 16 * GLOBAL_ROAD_SPRITE_WIDTH, 4 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_LEFT(16) }
#define T_RCURL3_B2		{ 17 * GLOBAL_ROAD_SPRITE_WIDTH, 4 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_RIGHT(MASK_NO - 16) }
#define T_RCURL3_C1		{ 18 * GLOBAL_ROAD_SPRITE_WIDTH, 4 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_LEFT(8) }
#define T_RCURL3_C2		{ 19 * GLOBAL_ROAD_SPRITE_WIDTH, 4 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_RIGHT(MASK_NO - 8) }

/* Grass Curve Left 2 x 1 */
#define T_GCURL2_A1		{ 0 * GLOBAL_ROAD_SPRITE_WIDTH, 5 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_GCURL2_A2		{ 1 * GLOBAL_ROAD_SPRITE_WIDTH, 5 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_GCURL2_B1		{ 2 * GLOBAL_ROAD_SPRITE_WIDTH, 5 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_GCURL2_B2		{ 3 * GLOBAL_ROAD_SPRITE_WIDTH, 5 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
/* Grass Curve Right 2 x 1 */
#define T_GCURR2_A1		{ 4 * GLOBAL_ROAD_SPRITE_WIDTH, 5 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_GCURR2_A2		{ 5 * GLOBAL_ROAD_SPRITE_WIDTH, 5 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_GCURR2_B1		{ 6 * GLOBAL_ROAD_SPRITE_WIDTH, 5 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_GCURR2_B2		{ 7 * GLOBAL_ROAD_SPRITE_WIDTH, 5 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
/* Grass Curve Right 3 x 1 */
#define T_GCURR3_A1		{ 8 * GLOBAL_ROAD_SPRITE_WIDTH, 5 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_GCURR3_A2		{ 9 * GLOBAL_ROAD_SPRITE_WIDTH, 5 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_GCURR3_B1		{ 10 * GLOBAL_ROAD_SPRITE_WIDTH, 5 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_GCURR3_B2		{ 11 * GLOBAL_ROAD_SPRITE_WIDTH, 5 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_GCURR3_C1		{ 12 * GLOBAL_ROAD_SPRITE_WIDTH, 5 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_GCURR3_C2		{ 13 * GLOBAL_ROAD_SPRITE_WIDTH, 5 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
/* Grass Curve Left 3 x 1 */
#define T_GCURL3_A1		{ 14 * GLOBAL_ROAD_SPRITE_WIDTH, 5 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_GCURL3_A2		{ 15 * GLOBAL_ROAD_SPRITE_WIDTH, 5 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_GCURL3_B1		{ 16 * GLOBAL_ROAD_SPRITE_WIDTH, 5 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_GCURL3_B2		{ 17 * GLOBAL_ROAD_SPRITE_WIDTH, 5 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_GCURL3_C1		{ 18 * GLOBAL_ROAD_SPRITE_WIDTH, 5 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_GCURL3_C2		{ 19 * GLOBAL_ROAD_SPRITE_WIDTH, 5 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }

/* Water Tiles */
#define T_WATER____		{ 0 * GLOBAL_ROAD_SPRITE_WIDTH, 6 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_BRIDGE_A2		{ 1 * GLOBAL_ROAD_SPRITE_WIDTH, 6 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_BRIDGE_A1		{ 2 * GLOBAL_ROAD_SPRITE_WIDTH, 6 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_RAIL___A1		{ 3 * GLOBAL_ROAD_SPRITE_WIDTH, 6 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_RAIL___A2		{ 4 * GLOBAL_ROAD_SPRITE_WIDTH, 6 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_RAIL___B1		{ 5 * GLOBAL_ROAD_SPRITE_WIDTH, 6 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_RAIL___B2		{ 6 * GLOBAL_ROAD_SPRITE_WIDTH, 6 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_RAIL___C1		{ 7 * GLOBAL_ROAD_SPRITE_WIDTH, 6 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_RAIL___C2		{ 8 * GLOBAL_ROAD_SPRITE_WIDTH, 6 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_TWATER_A1		{ 9 * GLOBAL_ROAD_SPRITE_WIDTH, 6 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_TWATER_A2		{ 10 * GLOBAL_ROAD_SPRITE_WIDTH, 6 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_TWATER_A3		{ 11 * GLOBAL_ROAD_SPRITE_WIDTH, 6 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_TWATER_A4		{ 12 * GLOBAL_ROAD_SPRITE_WIDTH, 6 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_TWATER_B1		{ 13 * GLOBAL_ROAD_SPRITE_WIDTH, 6 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_TWATER_B2		{ 14 * GLOBAL_ROAD_SPRITE_WIDTH, 6 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_TWATER_B3		{ 15 * GLOBAL_ROAD_SPRITE_WIDTH, 6 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_TWATER_B4		{ 16 * GLOBAL_ROAD_SPRITE_WIDTH, 6 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }

/* Bifurcartion Tiles */
#define T_BIF____A1		{ 0 * GLOBAL_ROAD_SPRITE_WIDTH, 7 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_RIGHT(16) }
#define T_BIF____A_		{ 1 * GLOBAL_ROAD_SPRITE_WIDTH, 7 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_BIF____A2		{ 2 * GLOBAL_ROAD_SPRITE_WIDTH, 7 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_LEFT(16) }
#define T_BIF____B1		{ 3 * GLOBAL_ROAD_SPRITE_WIDTH, 7 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_RIGHT(28) }
#define T_BIF____B_		{ 4 * GLOBAL_ROAD_SPRITE_WIDTH, 7 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_BIF____B2		{ 5 * GLOBAL_ROAD_SPRITE_WIDTH, 7 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_LEFT(28) }
#define T_BIF____C1		{ 6 * GLOBAL_ROAD_SPRITE_WIDTH, 7 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_RIGHT(32) }
#define T_BIF____C_		{ 7 * GLOBAL_ROAD_SPRITE_WIDTH, 7 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_BIF____C2		{ 8 * GLOBAL_ROAD_SPRITE_WIDTH, 7 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_LEFT(32) }
#define T_BIF____D1		{ 9 * GLOBAL_ROAD_SPRITE_WIDTH, 7 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_RIGHT(16) }
#define T_BIF____D_		{ 10 * GLOBAL_ROAD_SPRITE_WIDTH, 7 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_BIF____D2		{ 11 * GLOBAL_ROAD_SPRITE_WIDTH, 7 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_LEFT(16) }
#define T_BIF____E1		{ 12 * GLOBAL_ROAD_SPRITE_WIDTH, 7 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_RIGHT(28) }
#define T_BIF____E_		{ 13 * GLOBAL_ROAD_SPRITE_WIDTH, 7 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_BIF____E2		{ 14 * GLOBAL_ROAD_SPRITE_WIDTH, 7 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_LEFT(28) }
#define T_BIF____F1		{ 15 * GLOBAL_ROAD_SPRITE_WIDTH, 7 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_RIGHT(32) }
#define T_BIF____F_		{ 16 * GLOBAL_ROAD_SPRITE_WIDTH, 7 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_BIF____F2		{ 17 * GLOBAL_ROAD_SPRITE_WIDTH, 7 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_LEFT(32) }


/* Extended */
#define T_BIF_____A		{ 14 * GLOBAL_ROAD_SPRITE_WIDTH, 3 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_BIF_____B		{ 14 * GLOBAL_ROAD_SPRITE_WIDTH, 2 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }

#define T_HOUSE__A1		{ 6 * GLOBAL_ROAD_SPRITE_WIDTH, 1 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_HOUSE__A2		{ 7 * GLOBAL_ROAD_SPRITE_WIDTH, 1 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_HOUSE__B1		{ 8 * GLOBAL_ROAD_SPRITE_WIDTH, 1 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_HOUSE__B2		{ 9 * GLOBAL_ROAD_SPRITE_WIDTH, 1 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_HOUSE__C1		{ 10 * GLOBAL_ROAD_SPRITE_WIDTH, 1 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_HOUSE__C2		{ 11 * GLOBAL_ROAD_SPRITE_WIDTH, 1 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }

#define T_START____		{ 12 * GLOBAL_ROAD_SPRITE_WIDTH, 1 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_NO }
#define T_START___A		{ 13 * GLOBAL_ROAD_SPRITE_WIDTH, 1 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_LEFT(4) }
#define T_START___B		{ 14 * GLOBAL_ROAD_SPRITE_WIDTH, 1 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_RIGHT(4) }

#define T_LAKE___A1		{ 15 * GLOBAL_ROAD_SPRITE_WIDTH, 0 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_LAKE___A2		{ 16 * GLOBAL_ROAD_SPRITE_WIDTH, 0 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_LAKE___A3		{ 17 * GLOBAL_ROAD_SPRITE_WIDTH, 0 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_LAKE___A4		{ 18 * GLOBAL_ROAD_SPRITE_WIDTH, 0 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_LAKE___A5		{ 19 * GLOBAL_ROAD_SPRITE_WIDTH, 0 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }

#define T_LAKE___B1		{ 8 * GLOBAL_ROAD_SPRITE_WIDTH, 9 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL } 
#define T_LAKE___B2		{ 9 * GLOBAL_ROAD_SPRITE_WIDTH, 9 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_LAKE___B3		{ 10 * GLOBAL_ROAD_SPRITE_WIDTH, 9 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_LAKE___B4		{ 8 * GLOBAL_ROAD_SPRITE_WIDTH, 8 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL } 
#define T_LAKE___B5		{ 9 * GLOBAL_ROAD_SPRITE_WIDTH, 8 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_LAKE___B6		{ 10 * GLOBAL_ROAD_SPRITE_WIDTH, 8 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }

#define T_LAKE__C01		{ 15 * GLOBAL_ROAD_SPRITE_WIDTH, 3 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_LAKE__C02		{ 16 * GLOBAL_ROAD_SPRITE_WIDTH, 3 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_LAKE__C03		{ 17 * GLOBAL_ROAD_SPRITE_WIDTH, 3 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_LAKE__C04		{ 18 * GLOBAL_ROAD_SPRITE_WIDTH, 3 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_LAKE__C05		{ 19 * GLOBAL_ROAD_SPRITE_WIDTH, 3 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_LAKE__C06		{ 15 * GLOBAL_ROAD_SPRITE_WIDTH, 2 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_LAKE__C07		{ 16 * GLOBAL_ROAD_SPRITE_WIDTH, 2 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_LAKE__C08		{ 17 * GLOBAL_ROAD_SPRITE_WIDTH, 2 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_LAKE__C09		{ 18 * GLOBAL_ROAD_SPRITE_WIDTH, 2 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_LAKE__C10		{ 19 * GLOBAL_ROAD_SPRITE_WIDTH, 2 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_LAKE__C11		{ 15 * GLOBAL_ROAD_SPRITE_WIDTH, 1 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_LAKE__C12		{ 16 * GLOBAL_ROAD_SPRITE_WIDTH, 1 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_LAKE__C13		{ 17 * GLOBAL_ROAD_SPRITE_WIDTH, 1 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_LAKE__C14		{ 18 * GLOBAL_ROAD_SPRITE_WIDTH, 1 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_LAKE__C15		{ 19 * GLOBAL_ROAD_SPRITE_WIDTH, 1 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }

#define T_BOAT___A1		{ 18 * GLOBAL_ROAD_SPRITE_WIDTH, 7 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_BOAT___A2		{ 19 * GLOBAL_ROAD_SPRITE_WIDTH, 7 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }

#define T_SHIP___A1		{ 17 * GLOBAL_ROAD_SPRITE_WIDTH, 6 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_SHIP___A2		{ 18 * GLOBAL_ROAD_SPRITE_WIDTH, 6 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_SHIP___A3		{ 19 * GLOBAL_ROAD_SPRITE_WIDTH, 6 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }

#define T_SHIP__B01		{ 0 * GLOBAL_ROAD_SPRITE_WIDTH, 8 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_SHIP__B02		{ 1 * GLOBAL_ROAD_SPRITE_WIDTH, 8 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_SHIP__B03		{ 2 * GLOBAL_ROAD_SPRITE_WIDTH, 8 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_SHIP__B04		{ 3 * GLOBAL_ROAD_SPRITE_WIDTH, 8 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_SHIP__B05		{ 4 * GLOBAL_ROAD_SPRITE_WIDTH, 8 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_SHIP__B06		{ 5 * GLOBAL_ROAD_SPRITE_WIDTH, 8 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_SHIP__B07		{ 6 * GLOBAL_ROAD_SPRITE_WIDTH, 8 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_SHIP__B08		{ 7 * GLOBAL_ROAD_SPRITE_WIDTH, 8 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_SHIP__B09		{ 0 * GLOBAL_ROAD_SPRITE_WIDTH, 9 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_SHIP__B10		{ 1 * GLOBAL_ROAD_SPRITE_WIDTH, 9 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_SHIP__B11		{ 2 * GLOBAL_ROAD_SPRITE_WIDTH, 9 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_SHIP__B12		{ 3 * GLOBAL_ROAD_SPRITE_WIDTH, 9 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_SHIP__B13		{ 4 * GLOBAL_ROAD_SPRITE_WIDTH, 9 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_SHIP__B14		{ 5 * GLOBAL_ROAD_SPRITE_WIDTH, 9 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_SHIP__B15		{ 6 * GLOBAL_ROAD_SPRITE_WIDTH, 9 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }
#define T_SHIP__B16		{ 7 * GLOBAL_ROAD_SPRITE_WIDTH, 9 * GLOBAL_ROAD_SPRITE_HEIGHT, MASK_ALL }


#endif /* __ROAD_SPRITE_H__ */
