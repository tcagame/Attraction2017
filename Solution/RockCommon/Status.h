#pragma once
#include <array>
#include "define.h"

const int ROCK_PLAYER_NUM = 4;

struct ROCK_DATA {
	struct STATUS {
		char device_x;
		char device_y;
		unsigned char device_button;
		unsigned char state;
		unsigned char continue_num;
		unsigned char toku;
		unsigned char item;
		unsigned char money;
		unsigned char power;
		STATUS( ) :
			device_x( 0 ),
			device_y( 0 ),
			device_button( 0b00000000 ),
			state( STATE_NONE ),
			continue_num( 0 ),
			toku( 0 ),
			item( 0b00000000 ),
			money( 0 ),
			power( 0 ) {
		}
	};
	std::array< STATUS, ROCK_PLAYER_NUM > player;
};

