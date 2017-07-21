#include "StatusSender.h"
#include "Device.h"

const int RESET_TIME = 15;//ÇªÇÃÇ§ÇøçÌèúÇ∑ÇÈ

StatusSender::StatusSender( ) {
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		_data.player[ i ] = ROCK_DATA::STATUS( );
	}
}


StatusSender::~StatusSender( ) {
}

void StatusSender::update( ) {
	DevicePtr device( Device::getTask( ) );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		_data.player[ i ].device_x = device->getDirX( i );
		_data.player[ i ].device_y = device->getDirY( i );
		_data.player[ i ].device_button = device->getButton( i );
	}
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		if ( _data.player[ i ].device_button == 15 ) {
			_reset_count[ i ]++;
		} else {
			_reset_count[ i ] = 0;
		}
	}
	
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		if ( _reset_count[ i ] > RESET_TIME ) {
			_data.player[ i ] = ROCK_DATA::STATUS( );
			_data.player[ i ].state = STATE_ENTRY;
		}
	}
}

ROCK_DATA StatusSender::getData( ) const {
	return _data;
}

bool StatusSender::setContinueNum( int idx, int num ) {
	if ( idx < 0 || idx >= ROCK_PLAYER_NUM ) {
		return false;
	}
	_data.player[ idx ].continue_num = num;
	return true;
}

