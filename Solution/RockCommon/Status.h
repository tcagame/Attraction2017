#pragma once
#include <array>
#include "define.h"
#include "Data.h"
#include <assert.h>

class Status : public Data {
public:

	static const int PLAYER_NUM = 4;

	struct Player {
		char device_x;
		char device_y;
		unsigned char device_button;
		unsigned char state;
		unsigned char continue_num;
		unsigned char toku;
		unsigned char item;
		unsigned char money;
		signed int power;
	};

	Status( ) {
		for ( int i = 0; i < PLAYER_NUM; i++ ) {
			_player[ i ].device_x = 0;
			_player[ i ].device_y = 0;
			_player[ i ].device_button = 0b00000000;
			_player[ i ].state = STATE_NONE;
			_player[ i ].continue_num = 0;
			_player[ i ].toku = 0;
			_player[ i ].item = 0b00000000;
			_player[ i ].money = 0;
			_player[ i ].power = 1;
		}
	};

	virtual ~Status( ) {

	}

	Player& getPlayer( int idx ) {
		assert( idx >= 0 );
		assert( idx < PLAYER_NUM );

		return _player[ idx ];
	}

	void * getPtr( ) {
		return ( void * )_player;
	}

	int getSize( ) {
		return sizeof( _player );
	}

private:
#	pragma pack( 1 )
		Player _player[ PLAYER_NUM ];
#	pragma pack( )
};

