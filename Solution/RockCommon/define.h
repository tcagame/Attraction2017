#pragma once

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = ( SCREEN_WIDTH * 9 ) / 16;

const int MESSAGE_COUNT = 10;

const unsigned int STATE_NONE		= 0b0000000000000000;
const unsigned int STATE_ENTRY		= 0b0000000000000001;
const unsigned int AREA_STREET_1	= 0b0000000000000010;
const unsigned int AREA_STREET_2	= 0b0000000000000100; //ボス戦
const unsigned int AREA_STREET_3	= 0b0000000000001000;
const unsigned int STATE_BOSS		= 0b0000000000010000; //多分使わない
const unsigned int STATE_RESULT		= 0b0000000000100000;
const unsigned int STATE_TEST		= 0b0000000001000000;

const unsigned int ITEM_ENHANCED_ATTACK	= 0b00000001;

const int ROCK_PLAYER_NUM = 4;
const int ROCK_PLAYER_MOTION_NUM = 10;
const double GRAVITY = -0.1;
const int COLLISION_RANGE = 20;

enum DOLL {
	DOLL_TAROSUKE_WAIT,
	DOLL_TAROSUKE_JUMP,
	DOLL_TAROSUKE_WALK,
	DOLL_TAROSUKE_DEAD,
	DOLL_TAROSUKE_CHARGE,
	DOLL_TAROSUKE_WISH,
	DOLL_GARISUKE_WAIT = DOLL_TAROSUKE_WAIT + ROCK_PLAYER_MOTION_NUM,
	DOLL_GARISUKE_JUMP,
	DOLL_GARISUKE_WALK,
	DOLL_GARISUKE_DEAD,
	DOLL_GARISUKE_CHARGE,
	DOLL_GARISUKE_WISH,
	DOLL_TAROJIRO_WAIT = DOLL_GARISUKE_WAIT + ROCK_PLAYER_MOTION_NUM,
	DOLL_TAROJIRO_JUMP,
	DOLL_TAROJIRO_WALK,
	DOLL_TAROJIRO_DEAD,
	DOLL_TAROJIRO_CHARGE,
	DOLL_TAROJIRO_WISH,
	DOLL_TAROMI_WAIT = DOLL_TAROJIRO_WAIT + ROCK_PLAYER_MOTION_NUM,
	DOLL_TAROMI_JUMP,
	DOLL_TAROMI_WALK,
	DOLL_TAROMI_DEAD,
	DOLL_TAROMI_CHARGE,
	DOLL_TAROMI_WISH,

	DOLL_ANCESTORS,

	DOLL_ENEMY_START,
	DOLL_GHOST,
	DOLL_REDBARD,
	DOLL_WATERGHOST,

	DOLL_DANGO,
	DOLL_MONEY_1,
	DOLL_MONEY_2,
	DOLL_MONEY_3,
	DOLL_MONEY_4,
	DOLL_CASKET,

	DOLL_ALTER_BEFORE,
	DOLL_ALTER_AFTER,

	MAX_DOLL,
	DOLL_NONE
};

enum EFFECT {
	EFFECT_SHOT,
	EFFECT_CHARGE,
	EFFECT_IMPACT,
	MAX_EFFECT
};