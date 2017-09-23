#pragma once

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const int ACE_MAP_SIZE = 8;

const double GRAVITY = 1.0;

const int EVENT_PAGE_NUM = 5;
const int SMALL_CHAR_GRAPH_SIZE = 32;
const int NORMAL_CHAR_GRAPH_SIZE = 64;
const int BIG_CHAR_GRAPH_SIZE = 128;
const int IMPACT_GRAPH_SIZE = 128;

const int PLAYER_CHAR_GRAPH_FOOT = 7;
const int PLAYER_CHAR_CHIP_WIDTH = 16;
const int EFFECT_CHIP_WIDTH = 8;
const int ENEMY_NORMAL_CHIP_WIDTH = 20;
const int ENEMY_SMALL_CHIP_WIDTH = 8;
const int ENEMY_BIG_CHIP_WIDTH = 16;
const int IMPACT_CHIP_WIDTH = 4;
const int ITEM_CHIP_WIDTH = 4;
const int VIEW_TITLE_Y = 0;
const int VIEW_WIDTH = 256;
const int VIEW_EVENT_HEIGHT = 256;
const int VIEW_STREET_HEIGHT = 256;
const int VIEW_STATUS_WIDTH = 320;
const int VIEW_STATUS_Y = VIEW_EVENT_HEIGHT + VIEW_STREET_HEIGHT;
const int VIEW_STREET_Y = 256;
const int VIEW_EVENT_Y = 0;

enum PLAYER {
	PLAYER_TAROSUKE,
	PLAYER_TAROJIRO,
	PLAYER_GARISUKE,
	PLAYER_TAROMI,
	MAX_PLAYER,
};

enum DIR {
	DIR_LEFT,
	DIR_RIGHT,
};

enum AREA {
	AREA_STREET,
	AREA_EVENT,
	MAX_AREA
};

enum EVENT {
	EVENT_NONE,
	EVENT_REDDAEMON,
	EVENT_FLAME,
	EVENT_WOOD,
	EVENT_MINERAL,
	EVENT_SHOP,
	EVENT_RYUGU,
	EVENT_LAKE,
	EVENT_CALL,
	EVENT_GAMBLE,
	EVENT_ENMA,
	EVENT_BUDHA,
	MAX_EVENT,
};

enum MESSAGE {
	MESSAGE_GAMBLE0,
	MESSAGE_GAMBLE1,
	MESSAGE_GAMBLE2,
	MESSAGE_MIKO,
	MESSAGE_RYUGU,
	MESSAGE_ENMA,
	MESSAGE_BUDHA,
	MAX_MESSAGE,
};


// Editor用
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
const unsigned char OBJECT_GRAY_MIST		= 0x0A;
const unsigned char OBJECT_STONE_FACE		= 0x0B;
const unsigned char OBJECT_NO_NECK_GHOST	= 0x0C;
const unsigned char OBJECT_SHISHIMAI_DAEMON	= 0x0D;
const unsigned char OBJECT_SHISHIMAI		= 0x0E;
const unsigned char OBJECT_ARCHER			= 0x0F;
const unsigned char OBJECT_HAND				= 0x10;
const unsigned char OBJECT_RED_BIRD			= 0x11;
const unsigned char OBJECT_BLUE_MONK		= 0x12;
//const unsigned char OBJECT_RED_DAEMON_JR	= 0x13;
const unsigned char OBJECT_GREEN_ZOMBIE		= 0x14;
const unsigned char OBJECT_HUG_DAEMON		= 0x15;
const unsigned char OBJECT_SWAMP_ZOMBIE_A	= 0x16;
const unsigned char OBJECT_SWAMP_ZOMBIE_B	= 0x17;
const unsigned char OBJECT_SWAMP_ZOMBIE_C	= 0x18;
// big
const unsigned char OBJECT_SKELETON			= 0x19;
const unsigned char OBJECT_LADY				= 0x1A;
const unsigned char OBJECT_WIND				= 0x1B;
const unsigned char OBJECT_ONYUDO			= 0x1C;
const unsigned char OBJECT_JIZO				= 0x1D;
const unsigned char OBJECT_TREE				= 0x1E;
const unsigned char OBJECT_GAMA				= 0x1F;
// small
const unsigned char OBJECT_FLOG				= 0x20;
const unsigned char OBJECT_BAT				= 0x21;
const unsigned char OBJECT_STONE			= 0x22;
const unsigned char OBJECT_MOTH 			= 0x23;
const unsigned char OBJECT_EYE_DAEMON		= 0x24;
// 水棲妖怪
const unsigned char OBJECT_SHELL			= 0x25;
const unsigned char OBJECT_RAY				= 0x26;
const unsigned char OBJECT_WATER_GHOST		= 0x27;
// イベント
const unsigned char OBJECT_TURTLE			= 0x28;

const unsigned char OBJECT_ENEMY_END = 0x7F;
//block
const unsigned char OBJECT_BLOCK  = 0x80;
const unsigned char OBJECT_ONEWAY = 0x81;
const unsigned char OBJECT_WATER  = 0x82;
//item
const unsigned char OBJECT_MONEY_BAG	= 0xA0;
const unsigned char OBJECT_MONEY_PURSE	= 0xA1;
const unsigned char OBJECT_MONEY_500	= 0xA2;
const unsigned char OBJECT_MONEY_1000	= 0xA3;
const unsigned char OBJECT_MONEY_5000	= 0xA4;
const unsigned char OBJECT_MONEY_10000	= 0xA5;
//event
const unsigned char OBJECT_EVENT_REDDAEMON = 0xC0;
const unsigned char OBJECT_EVENT_FLAME	   = 0xC1;
const unsigned char OBJECT_EVENT_WOOD	   = 0xC2;
const unsigned char OBJECT_EVENT_MINERAL   = 0xC3;
const unsigned char OBJECT_EVENT_SHOP	   = 0xC4;
const unsigned char OBJECT_EVENT_LAKE	   = 0xC5;
const unsigned char OBJECT_EVENT_RYUGU	   = 0xC6;
const unsigned char OBJECT_EVENT_CALL	   = 0xC7;
const unsigned char OBJECT_EVENT_GAMBLE    = 0xC8;
