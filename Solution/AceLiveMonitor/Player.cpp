#include "Player.h"
#include "Device.h"
#include "Armoury.h"
#include "ace_define.h"
#include "Family.h"

//画像サイズ
const int PLAYER_FOOT = 7;
//速度
const int MAX_SPEED = 20;
const int MOVE_SPEED = 7;
const int BRAKE_ACCEL = 1;
const int JUMP_POWER = -15;
//攻撃関係
const int CHARGE_PHASE_COUNT = 25;
const int MAX_CHARGE_COUNT = CHARGE_PHASE_COUNT * 4 - 1;
const int BURST_TIME = 60;
//アニメーション
const int PLAYER_ANIM_WAIT_COUNT = 12;
const int PLAYER_ANIM_WIDTH_NUM = 8;

Player::Player( int player_id, Vector pos ) :
Character( pos, NORMAL_CHAR_GRAPH_SIZE ),
_charge_count( 0 ),
_over_charge_time( -1 ),
_id( player_id ),
_action( ACTION_WAIT ) {
	setDir( DIR_RIGHT );
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
		break;
	case ACTION_CHARGE:
		actOnCharge( );
		break;
	case ACTION_OVER_CHARGE:
		actOnOverCharge( );
		break;
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
		return;
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
	if ( device->getDirY( _id ) > 0 ) {
		_action = ACTION_CHARGE;
		return;
	}
	if ( isStanding( ) && device->getPush( _id ) & BUTTON_C ) {
		_action = ACTION_FLOAT;
		vec.y = JUMP_POWER;
	}
	setVec( vec );
	_charge_count -= 2;
	if ( _charge_count < 0 ) {
		_charge_count = 0;
	}
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
	int power = ( _charge_count / CHARGE_PHASE_COUNT ) + 1;
	ShotPtr shot( new Shot( getPos( ), getDir( ), power ) );
	Armoury::getTask( )->add( shot );
	_action = ACTION_WAIT;
	_charge_count = 0;
}

void Player::actOnCharge( ) {
	DevicePtr device( Device::getTask( ) );
	if ( !isStanding( ) ) {
		_action = ACTION_FLOAT;
		return;
	}
	if ( device->getPush( _id ) & BUTTON_A ) {
		_action = ACTION_ATTACK;
		return;
	}
	if ( device->getDirY( _id ) <= 0 ) {
		if ( device->getDirX( _id ) == 0 ) {
			_action = ACTION_WAIT;
			return;
		}
		Vector vec = getVec( );
		if ( device->getPush( _id ) & BUTTON_C ) {
			vec.y = JUMP_POWER;
			setVec( vec );
			_action = ACTION_FLOAT;
			return;
		}
	}
	_charge_count++;
	if ( _charge_count > MAX_CHARGE_COUNT ) {
		_charge_count = 0;
		_over_charge_time = getActCount( );
		_action = ACTION_OVER_CHARGE;
	}
}

void Player::actOnOverCharge( ) {
	if ( _over_charge_time < 0 ) {
		_action = ACTION_WAIT;
		return;
	}

	if ( getActCount( ) - _over_charge_time > BURST_TIME ) {
		_action = ACTION_WAIT;
		_over_charge_time = -1;
	}
}

void Player::actOnCamera( ) {
	FamilyConstPtr family( Family::getTask( ) );
	double camera_pos = family->getCameraPos( );
	if ( getPos( ).x + getVec( ).x - NORMAL_CHAR_GRAPH_SIZE / 2 < camera_pos ) {
		Vector pos( getPos( ) );
		pos.x = camera_pos + getChipSize( ) / 2;
		setPos( pos );
		Vector vec( getVec( ) );
		vec.x = 0;
		setVec( vec );
	}
	if ( getPos( ).x + getVec( ).x + getChipSize( ) / 2 > camera_pos + SCREEN_WIDTH ) {
		Vector pos( getPos( ) );
		pos.x = ( camera_pos + SCREEN_WIDTH ) - getChipSize( ) / 2;
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
	chip.size = NORMAL_CHAR_GRAPH_SIZE;
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
	case ACTION_CHARGE:
		{
			const int ANIM[ ] = {
				32, 33, 34, 35, 36, 37, 38
			};
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			cx = ANIM[ ( _charge_count / ( CHARGE_PHASE_COUNT / 2 ) ) % anim_num ] % PLAYER_ANIM_WIDTH_NUM;
			cy = ANIM[ ( _charge_count / ( CHARGE_PHASE_COUNT / 2 ) ) % anim_num ] / PLAYER_ANIM_WIDTH_NUM;
		}
		break;
	case ACTION_OVER_CHARGE:
		{
			const int ANIM[ ] = {
				40, 41
			};
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			cx = ANIM[ ( getActCount( ) / PLAYER_ANIM_WAIT_COUNT ) % anim_num ] % PLAYER_ANIM_WIDTH_NUM;
			cy = ANIM[ ( getActCount( ) / PLAYER_ANIM_WAIT_COUNT ) % anim_num ] / PLAYER_ANIM_WIDTH_NUM;
		}
		break;
	}

	
	chip.tx = cx * NORMAL_CHAR_GRAPH_SIZE;
	chip.ty = cy * NORMAL_CHAR_GRAPH_SIZE;
	Vector pos = getPos( );
	if ( getDir( ) == DIR_LEFT ) {
		chip.sx1 = (int)pos.x - NORMAL_CHAR_GRAPH_SIZE / 2;
		chip.sy1 = (int)pos.y - NORMAL_CHAR_GRAPH_SIZE + PLAYER_FOOT;
		chip.sx2 = chip.sx1 + NORMAL_CHAR_GRAPH_SIZE;
		chip.sy2 = chip.sy1 + NORMAL_CHAR_GRAPH_SIZE;
	} else {
		chip.sx1 = (int)pos.x - NORMAL_CHAR_GRAPH_SIZE / 2 + NORMAL_CHAR_GRAPH_SIZE;
		chip.sy1 = (int)pos.y - NORMAL_CHAR_GRAPH_SIZE + PLAYER_FOOT;
		chip.sx2 = chip.sx1 - NORMAL_CHAR_GRAPH_SIZE;
		chip.sy2 = chip.sy1 + NORMAL_CHAR_GRAPH_SIZE;
	}
	return chip;
}

int Player::getChargeCount( ) const {
	return _charge_count;
}

Chip Player::getChargeChip( ) const {
	if ( !( _charge_count > 0 ) ) {
		return Chip( );
	}

	Chip chip = Chip( );
	Vector pos = getPos( );
	if ( getDir( ) == DIR_LEFT ) {
		chip.sx1 = (int)pos.x - NORMAL_CHAR_GRAPH_SIZE / 2;
		chip.sy1 = (int)pos.y - NORMAL_CHAR_GRAPH_SIZE + PLAYER_FOOT;
		chip.sx2 = chip.sx1 + NORMAL_CHAR_GRAPH_SIZE;
		chip.sy2 = chip.sy1 + NORMAL_CHAR_GRAPH_SIZE;
	} else {
		chip.sx1 = (int)pos.x - NORMAL_CHAR_GRAPH_SIZE / 2 + NORMAL_CHAR_GRAPH_SIZE;
		chip.sy1 = (int)pos.y - NORMAL_CHAR_GRAPH_SIZE + PLAYER_FOOT;
		chip.sx2 = chip.sx1 - NORMAL_CHAR_GRAPH_SIZE;
		chip.sy2 = chip.sy1 + NORMAL_CHAR_GRAPH_SIZE;
	}
	const int ANIM[ ] = {
		2, 3, 4, 5, 6, 7, 8, 9, 10, 11
	};
	int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	int phase = ( _charge_count / CHARGE_PHASE_COUNT ) * 2;
	int time = ( getActCount( ) / 2 ) % 2;
	chip.tx = ( ANIM[ phase + time ] % PLAYER_ANIM_WIDTH_NUM ) * NORMAL_CHAR_GRAPH_SIZE;
	chip.ty = ( ANIM[ phase + time ] / PLAYER_ANIM_WIDTH_NUM ) * NORMAL_CHAR_GRAPH_SIZE;
	chip.size = NORMAL_CHAR_GRAPH_SIZE;

	return chip;
}