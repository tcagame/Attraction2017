#pragma once

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = ( SCREEN_WIDTH * 9 ) / 16;

const int MESSAGE_COUNT = 10;

const unsigned char STATE_NONE		= 0b00000000;
const unsigned char STATE_ENTRY		= 0b00000001;
const unsigned char AREA_STREET_1	= 0b00000010;
const unsigned char AREA_STREET_2	= 0b00000100; //�{�X��
const unsigned char AREA_STREET_3	= 0b00001000;
const unsigned char STATE_BOSS		= 0b00010000; //�����g��Ȃ�
const unsigned char STATE_RESULT	= 0b00100000;
const unsigned char STATE_TEST		= 0b01000000;

const int MAX_ITEM_NUM = 7;
const unsigned char ITEM_DANGO           = 0b00000001;//�c�q
const unsigned char ITEM_HEART           = 0b00000010;//�n�[�g
const unsigned char ITEM_ENHANCED_ATTACK = 0b00000100;//�U������
const unsigned char ITEM_ENHANCED_CHARGE = 0b00001000;//������
const unsigned char ITEM_FIRE            = 0b00010000;//�_��i�΁j
const unsigned char ITEM_ROCK            = 0b00100000;//�_��i��j
const unsigned char ITEM_TREE            = 0b01000000;//�_��i�؁j

const int ROCK_PLAYER_NUM = 4;
const int ROCK_PLAYER_MOTION_NUM = 10;
const double GRAVITY = -0.4;
const int COLLISION_RANGE = 20;
const int MAX_PLAYER_SHOT_POWER = 4;
const int MAX_POWER = 16;

//�J�ڌn
const int TRANSITION_TOKU_NUM = 10;
const int TRANSITION_MONEY_NUM = 50000;

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
	DOLL_FACE_AND_HAND,
	DOLL_CLOUD,
	DOLL_BOSS_ROCK,
	DOLL_BAT,
	DOLL_KIMONO,

	DOLL_DANGO,
	DOLL_MONEY_1,
	DOLL_MONEY_2,
	DOLL_MONEY_3,
	DOLL_MONEY_4,
	DOLL_MONEY_5,
	DOLL_MONEY_6,
	DOLL_TOKU,
	DOLL_CASKET,
	DOLL_SACRED_ROCK,
	DOLL_SACRED_FIRE,
	DOLL_SACRED_TREE,
	DOLL_BUBBLE,

	DOLL_ALTER_BEFORE,
	DOLL_ALTER_AFTER,

	DOLL_TURTLE,

	MAX_DOLL,
	DOLL_NONE
};

enum EFFECT {
	EFFECT_SHOT,
	EFFECT_CHARGE_SHOT,
	EFFECT_CHARGE,
	EFFECT_SHOT_BACK,
	EFFECT_ANCESTORS_SHOT,
	EFFECT_IMPACT,
	MAX_EFFECT
};