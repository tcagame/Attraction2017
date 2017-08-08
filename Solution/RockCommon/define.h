#pragma once

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = ( SCREEN_WIDTH * 9 ) / 16;

const int MESSAGE_COUNT = 10;

const unsigned int STATE_NONE		= 0b00000000;
const unsigned int STATE_ENTRY		= 0b00000001;
const unsigned int STATE_STREET_1	= 0b00000010;
const unsigned int STATE_STREET_2	= 0b00000100;
const unsigned int STATE_STREET_3	= 0b00001000;
const unsigned int STATE_BOSS		= 0b00010000;
const unsigned int STATE_RESULT		= 0b00100000;
const unsigned int STATE_TEST		= 0b01000000;

const int ROCK_PLAYER_NUM = 4;
const int ROCK_PLAYER_MOTION_NUM = 10;
const double GRAVITY = -0.1;


enum DOLL {
	DOLL_TAROSUKE_WAIT,
	DOLL_TAROSUKE_JUMP,
	DOLL_TAROSUKE_WALK,
	DOLL_GARISUKE_WAIT = DOLL_TAROSUKE_WAIT + ROCK_PLAYER_MOTION_NUM,
	DOLL_GARISUKE_JUMP,
	DOLL_GARISUKE_WALK,
	DOLL_TAROJIRO_WAIT = DOLL_GARISUKE_WAIT + ROCK_PLAYER_MOTION_NUM,
	DOLL_TAROJIRO_JUMP,
	DOLL_TAROJIRO_WALK,
	DOLL_TAROMI_WAIT = DOLL_TAROJIRO_WAIT + ROCK_PLAYER_MOTION_NUM,
	DOLL_TAROMI_JUMP,
	DOLL_TAROMI_WALK,

	DOLL_ENEMY_START,
	DOLL_GHOST,
	DOLL_REDBARD,
	DOLL_WATERGHOST,
	MAX_DOLL
};