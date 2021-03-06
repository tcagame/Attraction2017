#pragma once
#include "Data.h"
#include <array>
#include "define.h"
#include <assert.h>

class Status : public Data {
public:

	static const int PLAYER_NUM = 4;
	static const int PLAYER_INIT_HP = 16;

	struct Player {
		char device_x;
		char device_y;
		unsigned char device_button;
		unsigned char area;
		unsigned char continue_num;
		unsigned char toku;
		unsigned char item;
		unsigned money;
		signed int power;
	};

	Status( ) {
		for ( int i = 0; i < PLAYER_NUM; i++ ) {
			_player[ i ].device_x = 0;
			_player[ i ].device_y = 0;
			_player[ i ].device_button = 0b00000000;
			_player[ i ].area = AREA_NONE;
			_player[ i ].continue_num = 0;
			_player[ i ].toku = 0;
			_player[ i ].item = 0b00000000;
			_player[ i ].money = 0;
			_player[ i ].power = PLAYER_INIT_HP;
		}
	};

	virtual ~Status( ) {

	};

	Player& getPlayer( int idx ) {
		assert( idx >= 0 );
		assert( idx < PLAYER_NUM );

		return _player[ idx ];
	};

	void * getPtr( ) {
		return ( void * )_player;
	};

	int getSize( ) {
		return sizeof( _player );
	};

	void resetPlayer( int idx ) {
		_player[ idx ].area = AREA_NONE;
		_player[ idx ].continue_num = 0;
		_player[ idx ].toku = 0;
		_player[ idx ].item = 0b00000000;
		_player[ idx ].money = 0;
		_player[ idx ].power = PLAYER_INIT_HP;
	};

private:
#	pragma pack( 1 )
		Player _player[ PLAYER_NUM ];
#	pragma pack( )
};

