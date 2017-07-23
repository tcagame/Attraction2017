#include "Player.h"
#include "Device.h"
#include "PsychicManager.h"
#include "Game.h"
#include "ace_define.h"

const int MAX_SPEED = 20;
const int MOVE_SPEED = 7;
const int BRAKE_ACCEL = 1;
const int WIDTH = 38;
const int JUMP_POWER = -15;

Player::Player( int player_id, Vector pos ) :
_id( player_id ),
_act_count( 0 ),
_pos( pos ),
_vec( Vector( ) ),
_action( ACTION_WAIT ) {
	_dir = DIR_RIGHT;
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
	case ACTION_ATTACK:
		actOnAttack( );
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
	if ( fabs( _vec.x ) > 0 ) {
		_action = ACTION_BRAKE;
	}
	DevicePtr device( Device::getTask( ) );
	if ( _standing && device->getButton( _id ) & BUTTON_C ) {
		_vec.y = JUMP_POWER;
		_action = ACTION_FLOAT;
		return;
	}
	if ( abs( device->getDirX( _id ) ) > 50 ) {
		_action = ACTION_WALK;
		_act_count = 0;
		return;
	}
	if ( device->getPush( ) & BUTTON_A ) {
		_action = ACTION_ATTACK;
	}

}

void Player::actOnWalking( ) {
	//スティックの入力が無い場合action_wait
	DevicePtr device( Device::getTask( ) );
	if ( device->getDirX( _id ) * _vec.x < 0 ||
		 device->getDirX( _id ) == 0 ) {
		if ( ( int )_vec.x == 0 ) {
			_action = ACTION_WAIT;
		} else {
			_action = ACTION_BRAKE;
		}
		_act_count = 0;
		return;
	}
	if ( _standing && device->getButton( _id ) & BUTTON_C ) {
		_vec.y = JUMP_POWER;
		_action = ACTION_FLOAT;
		return;
	}
	if ( !_standing ) {
		_action = ACTION_FLOAT;
		_act_count = 0;
		return;
	}
	if ( device->getDirX( _id ) < 50 ) {
		_vec.x = -MOVE_SPEED;
	}
	if ( device->getDirX( _id ) > 50 ) {
		_vec.x = MOVE_SPEED;
	}
}

void Player::actOnBreaking( ) {
	if ( ( int )_vec.x == 0 ) {
		_action = ACTION_WAIT;
		_act_count = 0;
	}
	DevicePtr device( Device::getTask( ) );
	if ( _standing && device->getButton( _id ) & BUTTON_C ) {
		_vec.y = JUMP_POWER;
		_action = ACTION_FLOAT;
		return;
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
	DevicePtr device( Device::getTask( ) );
	if ( device->getDirX( _id ) * _vec.x < 0 ) {
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
	if ( device->getPush( ) & BUTTON_A ) {
		_action = ACTION_ATTACK;
	}

}

void Player::actOnAttack( ) {
	GamePtr game = Game::getTask( );
	PsychicManagerPtr psychicmanager = game->getPsychicManager( );
	psychicmanager->shot( _pos, _dir );
	_action = ACTION_WAIT;
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