#pragma once

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const int ACE_PLAYER_NUM = 4;
const int ACE_MAP_NUM = 4;
const int ACE_MAP_SIZE = 8;

const double GRAVITY = 1.0;

const int EVENT_PAGE_NUM = 4;
const int MAX_EVENT = 10;
const int SMALL_CHAR_GRAPH_SIZE = 32;
const int NORMAL_CHAR_GRAPH_SIZE = 64;
const int BIG_CHAR_GRAPH_SIZE = 128;

const int VIEW_EVENT_Y = 0;
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
const int OBJECT_CHIP_SIZE = 16;
const int DISP_WIDTH = SCREEN_WIDTH - CHIP_WIDTH - CHIP_WIDTH / 2;
const int PREVIEW_HEIGHT = GRAPH_SIZE;
const int DISP_CHIP_WIDTH = 19;
const int DISP_CHIP_HEIGHT = 40;
const int MAP_HEIGHT = 40;
const int GUIDE_X = 0;
const int GUIDE_Y = 450 - CHIP_HEIGHT * MAP_HEIGHT / 2 - CHIP_HEIGHT;
const int PREVIEW_X = GUIDE_X + CHIP_WIDTH / 2;
const int PREVIEW_Y = SCREEN_HEIGHT - PREVIEW_HEIGHT;
const int OBJECT_CHIP_WIDTH_NUM = DISP_WIDTH / OBJECT_CHIP_SIZE;
const int OBJECT_CHIP_HEIGHT_NUM = PREVIEW_HEIGHT / OBJECT_CHIP_SIZE;
const int PAGE_CHIP_WIDTH_NUM = GRAPH_SIZE / CHIP_WIDTH;
const int PAGE_OBJECT_WIDTH_NUM = ( PAGE_CHIP_WIDTH_NUM * CHIP_WIDTH ) / OBJECT_CHIP_SIZE;
const int MAP_COVER_HEIGHT = 30;//‚½‚ë‚·‚¯ƒ‰ƒCƒ“

const int STRUCTURE_LIST_NUM = 100;
const int GROUND_LIST_NUM = 100;

//object
const unsigned char OBJECT_NONE   = 0x00;
//enemy
const unsigned char OBJECT_PURPLE_ZOMBIE	= 0x01;
const unsigned char OBJECT_FACE_AND_HAND	= 0x02;
const unsigned char OBJECT_NO_FACE			= 0x03;
const unsigned char OBJECT_LANCER			= 0x04;
const unsigned char OBJECT_CROCO_SNAKE		= 0x05;
const unsigned char OBJECT_GHOUL			= 0x06;
const unsigned char OBJECT_GHOST			= 0x07;
const unsigned char OBJECT_ONE_EYE_SNAKE	= 0x08;
const unsigned char OBJECT_WHITE_MIST		= 0x09;
const unsigned char OBJECT_STONE_FACE		= 0x0A;
const unsigned char OBJECT_NO_NECK_GHOST	= 0x0B;
const unsigned char OBJECT_SHISHIMAI_DEMON	= 0x0C;
const unsigned char OBJECT_SHISHIMAI		= 0x0D;
const unsigned char OBJECT_ARCHER			= 0x0E;
const unsigned char OBJECT_HAND				= 0x0F;
const unsigned char OBJECT_RED_BIRD			= 0x10;
const unsigned char OBJECT_BLUE_MONK		= 0x11;
//const unsigned char OBJECT_RED_DEMON_JR	= 0x12;
const unsigned char OBJECT_GREEN_ZOMBIE		= 0x13;
const unsigned char OBJECT_HUG_DEMON		= 0x14;
const unsigned char OBJECT_SWAMP_ZOMBIE_A	= 0x15;
const unsigned char OBJECT_SWAMP_ZOMBIE_B	= 0x16;
const unsigned char OBJECT_SWAMP_ZOMBIE_C	= 0x17;
// big
const unsigned char OBJECT_SKELETON			= 0x18;
const unsigned char OBJECT_LADY				= 0x19;
const unsigned char OBJECT_WIND				= 0x1A;
const unsigned char OBJECT_ONYUDO			= 0x1B;
const unsigned char OBJECT_JIZO				= 0x1C;
const unsigned char OBJECT_TREE				= 0x1D;


const unsigned char OBJECT_ENEMY_END = 0x7F;
//block
const unsigned char OBJECT_BLOCK  = 0x80;
const unsigned char OBJECT_ONEWAY = 0x81;
//event
const unsigned char OBJECT_EVENT_REDDEAMON = 0xC0;
const unsigned char OBJECT_EVENT_FIRE = 0xC1;
const unsigned char OBJECT_EVENT_TREE = 0xC2;
const unsigned char OBJECT_EVENT_ROCK = 0xC3;
const unsigned char OBJECT_EVENT_SHOP = 0xC4;

