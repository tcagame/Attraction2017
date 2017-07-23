#include "Player.h"
#include "Device.h"
#include "ace_define.h"

const int MAX_SPEED = 10;
const int MOVE_SPEED = 7;
const int BRAKE_ACCEL = 1;
const int WIDTH = 38;

Player::Player( Vector pos ) :
_act_count( 0 ),
_pos( pos ),
_vec( Vector( ) ),
_action( ACTION_WAIT ) {
}

Player::~Player( ) {
}

void Player::update( ) {
	_act_count++;
	switch ( _action ) {
	case ACTION_WAIT:
		actOnWaiting( );
		break;
	case ACTION_WALK:
		actOnWalking( );
		break;
	case ACTION_BRAKE:
		actOnBreaking( );
		break;
	case ACTION_FLOAT:
		actOnFloating( );
		break;
	}
	_standing = false;
	_vec.y += GRAVITY;
	if ( _vec.getLength( ) > MAX_SPEED ) {
		_vec = _vec.normalize( ) * MAX_SPEED;
	}
	if ( _pos.y + _vec.y > SCREEN_HEIGHT ) {
		_standing = true;
		_vec.y = 0;
		_pos.y = SCREEN_HEIGHT - GRAVITY / 2;
	}
	if ( _pos.x + _vec.x - WIDTH / 2 < 0 ) {
		_pos.x = WIDTH / 2;
		_vec.x = 0;
	}
	if ( _pos.x + _vec.x + WIDTH / 2 > SCREEN_WIDTH ) {
		_pos.x = SCREEN_WIDTH - WIDTH / 2;
		_vec.x = 0;
	}
	checkDir( );
	_pos += _vec;
}

void Player::actOnWaiting( ) {
	//デバイスのスティック入力があった場合、action_walk
	if ( !_standing ) {
		_action = ACTION_FLOAT;
		_act_count = 0;
		return;
	}
	DevicePtr device( Device::getTask( ) );
	if ( abs( device->getDirX( ) ) > 50 ) {
		_action = ACTION_WALK;
		_act_count = 0;
		return;
	}
}

void Player::actOnWalking( ) {
	//スティックの入力が無い場合action_wait
	DevicePtr device( Device::getTask( ) );
	if ( device->getDirX( ) * _vec.x < 0 ||
		 device->getDirX( ) == 0 ) {
		if ( ( int )_vec.x == 0 ) {
			_action = ACTION_WAIT;
		} else {
			_action = ACTION_BRAKE;
		}
		_act_count = 0;
		return;
	}
	if ( !_standing ) {
		_action = ACTION_FLOAT;
		_act_count = 0;
		return;
	}
	if ( device->getDirX( ) < 50 ) {
		_vec.x = -MOVE_SPEED;
	}
	if ( device->getDirX( ) > 50 ) {
		_vec.x = MOVE_SPEED;
	}
}

void Player::actOnBreaking( ) {
	if ( ( int )_vec.x == 0 ) {
		_action = ACTION_WAIT;
		_act_count = 0;
	}
	if ( !_standing ) {
		_action = ACTION_FLOAT;
		_act_count = 0;
		return;
	}
	if ( _vec.x < 0 ) {
		if ( _vec.x < -BRAKE_ACCEL ) {
			_vec.x += BRAKE_ACCEL;
		} else {
			_vec.x = 0;
		}
	}
	if ( _vec.x > 0 ) {
		if ( _vec.x > BRAKE_ACCEL ) {
			_vec.x -= BRAKE_ACCEL;
		} else {
			_vec.x = 0;
		}
	}
}

void Player::actOnFloating( ) {
	if ( _standing ) {
		_action = ACTION_WAIT;
		_act_count = 0;
		return;
	}	
}

Vector Player::getPos( ) const {
	return _pos;
}

Player::ACTION Player::getAction( ) const {
	return _action;
}

int Player::getActCount( ) const {
	return _act_count;
}

Player::DIR Player::getDir( ) const {
	return _dir;
}

void Player::checkDir( ) {
	if ( _vec.x > 0 ) {
		_dir = DIR_RIGHT;
	}
	if ( _vec.x < 0 ) {
		_dir = DIR_LEFT;
	}
}