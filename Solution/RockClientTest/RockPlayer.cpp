#include "RockPlayer.h"
#include "Status.h"
#include "Device.h"

const double JUMP_POWER = 3.0;
const double ANIM_SPEED = 0.2;

RockPlayer::RockPlayer( StatusPtr status, const Vector& pos, int id ) :
RockCharacter( pos, ( DOLL )( DOLL_TAROSUKE_WAIT + id * ROCK_PLAYER_MOTION_NUM ) ) {
	_id = id;
	_status = status;
	setAction( ACTION_WAIT );
}


RockPlayer::~RockPlayer( ) {
}

void RockPlayer::act( ) {
	switch ( _action ) {
	case ACTION_WAIT:
		actOnWaiting( );
		break;
	case ACTION_JUMP:
		actOnJumping( );
		break;
	}
}

void RockPlayer::setAction( ACTION action ) {
	_action = action;
	setActCount( 0 );
	switch ( _action ) {
	case ACTION_WAIT:
		setDoll( ( DOLL )( DOLL_TAROSUKE_WAIT + _id * ROCK_PLAYER_MOTION_NUM ) );
		break;
	case ACTION_JUMP:
		setDoll( ( DOLL )( DOLL_TAROSUKE_JUMP + _id * ROCK_PLAYER_MOTION_NUM ) );
		break;
	default:
		setDoll( ( DOLL )( DOLL_TAROSUKE_WAIT + _id * ROCK_PLAYER_MOTION_NUM ) );
		break;
	}
}

void RockPlayer::actOnWaiting( ) {
	Status::Player player = _status->getPlayer( _id );
	//ƒWƒƒƒ“ƒv
	if ( isStanding( ) ) {
		if ( player.device_button & BUTTON_A ) {
			setAction( ACTION_JUMP );
			Vector vec = getVec( );
			vec.y = JUMP_POWER;
			setVec( vec );
		}
	}
}
void RockPlayer::actOnJumping( ) {
	if ( isStanding( ) ) {
		setAction( ACTION_WAIT );
	}
}

double RockPlayer::getAnimTime( ) const {
	double anim_time = 0;
	switch ( _action ) {
	case ACTION_WAIT:		
		anim_time = ( double )getActCount( ) * ANIM_SPEED;
		break;
	case ACTION_JUMP:
		anim_time = ( double )getActCount( ) * ANIM_SPEED;
		break;
	default:
		anim_time = 0;
		break;
	}
	return anim_time;
}
