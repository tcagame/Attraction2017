#pragma once
#include <string>
#include "mathmatics.h"

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
			device_button( 0x00000000 ),
			state( 0x00000000 ),
			continue_num( 0x00000000 ),
			toku( 0x00000000 ),
			item( 0x00000000 ),
			money( 0x00000000 ),
			power( 0x00000000 ) {
		}
	};
	STATUS player[ ROCK_PLAYER_NUM ];
};

