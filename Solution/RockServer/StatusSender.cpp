#include "StatusSender.h"
#include "Device.h"
#include "Application.h"

const int RESET_TIME = 15;//そのうち削除する


StatusSenderPtr StatusSender::getTask( ) {
	return std::dynamic_pointer_cast< StatusSender >( Application::getInstance( )->getTask( getTag( ) ) );
}

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

bool StatusSender::setTokuNum( int idx, int num ) {
	if ( idx < 0 || idx >= ROCK_PLAYER_NUM ) {
		return false;
	}
	_data.player[ idx ].toku = num;
	return true;
}

bool StatusSender::setPower( int idx, int power ) {
	if ( idx < 0 || idx >= ROCK_PLAYER_NUM ) {
		return false;
	}
	_data.player[ idx ].power = power;
	return true;
}

bool StatusSender::setMoney( int idx, int money ) {
	if ( idx < 0 || idx >= ROCK_PLAYER_NUM ) {
		return false;
	}
	_data.player[ idx ].money = money;
	return true;
}

bool StatusSender::setItem( int idx, int item ) {
	if ( idx < 0 || idx >= ROCK_PLAYER_NUM ) {
		return false;
	}
	_data.player[ idx ].item = item;
	return true;
}

bool StatusSender::setState( int idx, unsigned int state ) {
	if ( idx < 0 || idx >= ROCK_PLAYER_NUM ) {
		return false;
	}
	_data.player[ idx ].state = state;
	return true;
}
