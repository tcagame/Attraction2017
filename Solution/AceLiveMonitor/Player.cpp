#include "Player.h"
#include "Device.h"
#include "Armoury.h"
#include "ace_define.h"

const int MAX_SPEED = 20;
const int MOVE_SPEED = 7;
const int BRAKE_ACCEL = 1;
const int WIDTH = 38;
const int JUMP_POWER = -15;

Player::Player( int player_id, Vector pos ) :
Character( pos, WIDTH ),
_id( player_id ),
_act_count( 0 ),
_action( ACTION_WAIT ) {
}

Player::~Player( ) {
}

void Player::act( ) {
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
	case ACTION_ATTACK:
		actOnAttack( );
	}
}

void Player::actOnWaiting( ) {
	//デバイスのスティック入力があった場合、action_walk
	if ( !isStanding( ) ) {
		_action = ACTION_FLOAT;
		_act_count = 0;
		return;
	}
	Vector vec = getVec( );
	if ( fabs( vec.x ) > 0 ) {
		_action = ACTION_BRAKE;
	}
	DevicePtr device( Device::getTask( ) );
	if ( isStanding( ) && device->getButton( _id ) & BUTTON_C ) {
		vec.y = JUMP_POWER;
		_action = ACTION_FLOAT;
		return;
	}
	if ( abs( device->getDirX( _id ) ) > 50 ) {
		_action = ACTION_WALK;
		_act_count = 0;
		return;
	}
	if ( device->getPush( _id ) & BUTTON_A ) {
		_action = ACTION_ATTACK;
	}
	setVec( vec );
}

void Player::actOnWalking( ) {
	//スティックの入力が無い場合action_wait
	DevicePtr device( Device::getTask( ) );
	Vector vec = getVec( );
	if ( device->getDirX( _id ) * vec.x < 0 ||
		 device->getDirX( _id ) == 0 ) {
		if ( ( int )( vec.x * 100 ) == 0 ) {
			_action = ACTION_WAIT;
		} else {
			_action = ACTION_BRAKE;
		}
		_act_count = 0;
		return;
	}
	if ( isStanding( ) && device->getButton( _id ) & BUTTON_C ) {
		vec.y = JUMP_POWER;
		_action = ACTION_FLOAT;
		return;
	}
	if ( !isStanding( ) ) {
		_action = ACTION_FLOAT;
		_act_count = 0;
		return;
	}
	if ( device->getDirX( _id ) < 50 ) {
		vec.x = -MOVE_SPEED;
	}
	if ( device->getDirX( _id ) > 50 ) {
		vec.x = MOVE_SPEED;
	}
	setVec( vec );
}

void Player::actOnBreaking( ) {
	Vector vec = getVec( );
	if ( ( int )vec.x == 0 ) {
		_action = ACTION_WAIT;
		_act_count = 0;
	}
	DevicePtr device( Device::getTask( ) );
	if ( isStanding( ) && device->getButton( _id ) & BUTTON_C ) {
		vec.y = JUMP_POWER;
		_action = ACTION_FLOAT;
		return;
	}
	if ( !isStanding( ) ) {
		_action = ACTION_FLOAT;
		_act_count = 0;
		return;
	}
	if ( vec.x < 0 ) {
		if ( vec.x < -BRAKE_ACCEL ) {
			vec.x += BRAKE_ACCEL;
		} else {
			vec.x = 0;
		}
	}
	if ( vec.x > 0 ) {
		if ( vec.x > BRAKE_ACCEL ) {
			vec.x -= BRAKE_ACCEL;
		} else {
			vec.x = 0;
		}
	}
	setVec( vec );
}

void Player::actOnFloating( ) {
	if ( isStanding( ) ) {
		_action = ACTION_WAIT;
		_act_count = 0;
		return;
	}	
	DevicePtr device( Device::getTask( ) );
	Vector vec = getVec( );
	if ( device->getDirX( _id ) * vec.x < 0 ) {
		if ( vec.x < 0 ) {
			if ( vec.x < -BRAKE_ACCEL ) {
				vec.x += BRAKE_ACCEL;
			} else {
				vec.x = 0;
			}
		}
		if ( vec.x > 0 ) {
			if ( vec.x > BRAKE_ACCEL ) {
				vec.x -= BRAKE_ACCEL;
			} else {
				vec.x = 0;
			}
		}
	}
	if ( device->getPush( _id ) & BUTTON_A ) {
		_action = ACTION_ATTACK;
	}

}

void Player::actOnAttack( ) {
	ArmouryPtr Armoury = Armoury::getTask( );
	Armoury->shot( getPos( ), getDir( ) );
	_action = ACTION_WAIT;
}

Player::ACTION Player::getAction( ) const {
	return _action;
}

int Player::getActCount( ) const {
	return _act_count;
}