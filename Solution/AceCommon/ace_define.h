#pragma once

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const int ACE_PLAYER_NUM = 4;
const int ACE_MAP_NUM = 4;
const int ACE_MAP_SIZE = 8;

const int GRAVITY = 1;

const int NORMAL_CHAR_GRAPH_SIZE = 64;

const int VIEW_TITLE_Y = 0;
const int VIEW_TITLE_HEIGHT = 256;
const int VIEW_STREET_Y = VIEW_TITLE_Y + VIEW_TITLE_HEIGHT;
const int VIEW_STREET_HEIGHT = 256;
const int VIEW_STATUS_Y = VIEW_STREET_Y + VIEW_STREET_HEIGHT;

enum DIR {
	DIR_LEFT,
	DIR_RIGHT,
};

struct Chip {
	int sx1;
	int sy1;
	int sx2;
	int sy2;
	int tx;
	int ty;
	int size;
	Chip( ) {
		sx1 = 0;
		sy1 = 0;
		sx2 = 0;
		sy2 = 0;
		tx = 0;
		ty = 0;
		size = 0;
	}
};

// Editor—p
const int GRAPH_SIZE = 256;
const int CHIP_WIDTH = 64;
const int CHIP_HEIGHT = 16;
const int OBJECT_GUIDE_SIZE = 16;
const int DISP_WIDTH = SCREEN_WIDTH - CHIP_WIDTH - CHIP_WIDTH / 2;
const int PREVIEW_HEIGHT = GRAPH_SIZE;
const int DISP_CHIP_WIDTH = 19;
const int DISP_CHIP_HEIGHT = 40;
const int MAP_HEIGHT = 40;
const int GUIDE_X = 0;
const int GUIDE_Y = 450 - CHIP_HEIGHT * MAP_HEIGHT / 2 - CHIP_HEIGHT;
const int PREVIEW_X = GUIDE_X + CHIP_WIDTH / 2;
const int PREVIEW_Y = SCREEN_HEIGHT - PREVIEW_HEIGHT;
const int OBJECT_CHIP_WIDTH_NUM = DISP_WIDTH / OBJECT_GUIDE_SIZE;
const int OBJECT_CHIP_HEIGHT_NUM = PREVIEW_HEIGHT / OBJECT_GUIDE_SIZE;
const int PAGE_CHIP_WIDTH_NUM = GRAPH_SIZE / CHIP_WIDTH;
const int PAGE_OBJECT_WIDTH_NUM = ( PAGE_CHIP_WIDTH_NUM * CHIP_WIDTH ) / OBJECT_GUIDE_SIZE;
const int MAP_COVER_HEIGHT = 30;//‚½‚ë‚·‚¯ƒ‰ƒCƒ“

const int STRUCTURE_LIST_NUM = 100;
const int GROUND_LIST_NUM = 100;

const unsigned char OBJECT_NONE  = 0x00000000;
const unsigned char OBJECT_BLOCK = 0x00000001;