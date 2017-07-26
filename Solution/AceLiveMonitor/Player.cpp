#include "Player.h"
#include "Device.h"
#include "Armoury.h"
#include "ace_define.h"
#include "Family.h"

//サイズ
const int PLAYER_FOOT = 7;
//速度
const int MAX_SPEED = 20;
const int MOVE_SPEED = 7;
const int BRAKE_ACCEL = 1;
const int JUMP_POWER = -15;
//アニメーション
const int PLAYER_ANIM_WAIT_COUNT = 12;
const int PLAYER_ANIM_WIDTH_NUM = 8;

Player::Player( int player_id, Vector pos ) :
Character( pos, NOMAL_CHAR_GRAPH_SIZE ),
_id( player_id ),
_action( ACTION_WAIT ) {
}

Player::~Player( ) {
}

void Player::act( ) {
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
	actOnCamera( );
}

void Player::actOnWaiting( ) {
	//デバイスのスティック入力があった場合、action_walk
	if ( !isStanding( ) ) {
		_action = ACTION_FLOAT;
		return;
	}
	Vector vec = getVec( );
	if ( fabs( vec.x ) > 0 ) {
		_action = ACTION_BRAKE;
	}
	DevicePtr device( Device::getTask( ) );
	if ( abs( device->getDirX( _id ) ) > 50 ) {
		_action = ACTION_WALK;
		return;
	}
	if ( device->getPush( _id ) & BUTTON_A ) {
		_action = ACTION_ATTACK;
		return;
	}
	if ( isStanding( ) && device->getPush( _id ) & BUTTON_C ) {
		_action = ACTION_FLOAT;
		vec.y = JUMP_POWER;
	}
	setVec( vec );
}

void Player::actOnWalking( ) {
	//スティックの入力が無い場合action_wait
	DevicePtr device( Device::getTask( ) );
	Vector vec = getVec( );
	if ( !isStanding( ) ) {
		_action = ACTION_FLOAT;
		return;
	}
	if ( device->getDirX( _id ) * vec.x < 0 ) {
		_action = ACTION_BRAKE;
		return;
	}
	if ( device->getDirX( _id ) == 0 ) {
		_action = ACTION_WAIT;
		return;
	}

	if ( isStanding( ) && device->getPush( _id ) & BUTTON_C ) {
		_action = ACTION_FLOAT;
		vec.y = JUMP_POWER;
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
	if ( !isStanding( ) ) {
		_action = ACTION_FLOAT;
		return;
	}
	if ( ( int )vec.x == 0 ) {
		_action = ACTION_WAIT;
	}
	DevicePtr device( Device::getTask( ) );
	if ( isStanding( ) && device->getPush( _id ) & BUTTON_C ) {
		vec.y = JUMP_POWER;
		_action = ACTION_FLOAT;
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
	ShotPtr shot( new Shot( getPos( ), getDir( ) ) );
	Armoury::getTask( )->add( shot );
	_action = ACTION_WAIT;
}

void Player::actOnCamera( ) {
	FamilyConstPtr family( Family::getTask( ) );
	double camera_pos = family->getCameraPos( );
	if ( getPos( ).x + getVec( ).x - NOMAL_CHAR_GRAPH_SIZE / 2 < camera_pos - SCREEN_WIDTH / 2 ) {
		Vector pos( getPos( ) );
		pos.x = ( camera_pos - SCREEN_WIDTH / 2 ) + getChipSize( ) / 2;
		setPos( pos );
		Vector vec( getVec( ) );
		vec.x = 0;
		setVec( vec );
	}
	if ( getPos( ).x + getVec( ).x + getChipSize( ) / 2 > camera_pos + SCREEN_WIDTH / 2 ) {
		Vector pos( getPos( ) );
		pos.x = ( camera_pos + SCREEN_WIDTH / 2 ) - getChipSize( ) / 2;
		setPos( pos );
		Vector vec( getVec( ) );
		vec.x = 0;
		setVec( vec );
	}
}

Player::ACTION Player::getAction( ) const {
	return _action;
}

Chip Player::getChip( ) const {
	Chip chip = Chip( );
	chip.size = NOMAL_CHAR_GRAPH_SIZE;
	int cx = 0;
	int cy = 0;
	switch ( _action ) {
	case ACTION_WAIT:
		{
			const int ANIM[ ] = {
				0,
			};
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			cx = ANIM[ ( getActCount( ) / PLAYER_ANIM_WAIT_COUNT ) % anim_num ] % PLAYER_ANIM_WIDTH_NUM;
			cy = ANIM[ ( getActCount( ) / PLAYER_ANIM_WAIT_COUNT ) % anim_num ] / PLAYER_ANIM_WIDTH_NUM;
		}
		break;
	case ACTION_WALK:
		{
			const int ANIM[ ] = {
				0, 1, 2, 1, 0, 3, 4, 3
			};
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			cx = ANIM[ ( ( int )getPos( ).x / PLAYER_ANIM_WAIT_COUNT ) % anim_num ] % PLAYER_ANIM_WIDTH_NUM;
			cy = ANIM[ ( ( int )getPos( ).x / PLAYER_ANIM_WAIT_COUNT ) % anim_num ] / PLAYER_ANIM_WIDTH_NUM;
		}
		break;
	case ACTION_BRAKE:
		{
			const int ANIM[ ] = {
				6,
			};
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			cx = ANIM[ ( ( int )getPos( ).x / PLAYER_ANIM_WAIT_COUNT ) % anim_num ] % PLAYER_ANIM_WIDTH_NUM;
			cy = ANIM[ ( ( int )getPos( ).x / PLAYER_ANIM_WAIT_COUNT ) % anim_num ] / PLAYER_ANIM_WIDTH_NUM;
		}
		break;
	case ACTION_FLOAT:
		{
			const int ANIM[ ] = {
				5,
			};
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			cx = ANIM[ ( ( int )getPos( ).x / PLAYER_ANIM_WAIT_COUNT ) % anim_num ] % PLAYER_ANIM_WIDTH_NUM;
			cy = ANIM[ ( ( int )getPos( ).x / PLAYER_ANIM_WAIT_COUNT ) % anim_num ] / PLAYER_ANIM_WIDTH_NUM;
		}
		break;
	}

	
	chip.tx = cx * NOMAL_CHAR_GRAPH_SIZE;
	chip.ty = cy * NOMAL_CHAR_GRAPH_SIZE;
	Vector pos = getPos( );
	if ( getDir( ) == DIR_LEFT ) {
		chip.sx1 = (int)pos.x - NOMAL_CHAR_GRAPH_SIZE / 2;
		chip.sy1 = (int)pos.y - NOMAL_CHAR_GRAPH_SIZE + PLAYER_FOOT;
		chip.sx2 = chip.sx1 + NOMAL_CHAR_GRAPH_SIZE;
		chip.sy2 = chip.sy1 + NOMAL_CHAR_GRAPH_SIZE;
	} else {
		chip.sx1 = (int)pos.x - NOMAL_CHAR_GRAPH_SIZE / 2 + NOMAL_CHAR_GRAPH_SIZE;
		chip.sy1 = (int)pos.y - NOMAL_CHAR_GRAPH_SIZE + PLAYER_FOOT;
		chip.sx2 = chip.sx1 - NOMAL_CHAR_GRAPH_SIZE;
		chip.sy2 = chip.sy1 + NOMAL_CHAR_GRAPH_SIZE;
	}
	return chip;
}