#include "RockPlayer.h"
#include "RockClientInfo.h"
#include "Status.h"
#include "Device.h"
#include "Drawer.h"
#include "RockFamily.h"
#include "RockEnemy.h"
#include "RockCharacter.h"
#include "RockMilitary.h"
#include "MessageSender.h"

const double JUMP_POWER = 3.0;
const double BOUND_POWER = 1.0;
const double ANIM_SPEED = 0.5;
const double MOVE_SPEED = 1.0;
const double BRAKE_SPEED = 0.3;

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
	case ACTION_WALK:
		actOnWalking( );
		break;
	case ACTION_BRAKE:
		actOnBraking( );
	}
	// カメラに入り続ける
	DrawerPtr drawer( Drawer::getTask( ) );
	if ( !drawer->isInCamera( getPos( ) + getVec( ) ) ) {
		setVec( Vector( ) );
	}
	Vector dir = ( RockFamily::getTask( )->getCameraPos( ) - getPos( ) ).normalize( );
	while( !drawer->isInCamera( getPos( ) + getVec( ) ) ) {
		setVec( getVec( ) + dir );
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
	case ACTION_WALK:
		setDoll( ( DOLL )( DOLL_TAROSUKE_WALK + _id * ROCK_PLAYER_MOTION_NUM ) );
		break;
	default:
		setDoll( ( DOLL )( DOLL_TAROSUKE_WAIT + _id * ROCK_PLAYER_MOTION_NUM ) );
		break;
	}
}

bool RockPlayer::isActive( ) const {
	return (  RockClientInfo::getTask( )->getClientId( ) == _status->getPlayer( _id ).state );
}

void RockPlayer::actOnWaiting( ) {
	Status::Player player = _status->getPlayer( _id );
	//ジャンプ
	if ( isStanding( ) ) {
		if ( player.device_button & BUTTON_A ) {
			setAction( ACTION_JUMP );
			Vector vec = getVec( );
			vec.y = JUMP_POWER;
			setVec( vec );
			return;
		}
	}
	//移動
	if ( player.device_x != 0 ||
		 player.device_y != 0 ) {
		setAction( ACTION_WALK );
		return;
	}
	//ブレーキ
	//水平方向のベクトル
	Vector vec = getVec( );
	vec.y = 0;
	//ベクトルがない場合待機に移行する
	if ( vec.getLength( ) > 0 ) {
		setAction( ACTION_BRAKE );
		return;
	}
}
void RockPlayer::actOnJumping( ) {
	if ( isStanding( ) ) {
		setAction( ACTION_WAIT );
		return;
	}
	//移動
	Status::Player player = _status->getPlayer( _id );
	Vector vec = Vector( player.device_x, 0, player.device_y ).normalize( ) * MOVE_SPEED;
	vec.y = getVec( ).y;
	setVec( vec );
}

void RockPlayer::actOnWalking( ) {
	Status::Player player = _status->getPlayer( _id );
	//ジャンプ
	if ( isStanding( ) ) {
		if ( player.device_button & BUTTON_A ) {
			setAction( ACTION_JUMP );
			Vector vec = getVec( );
			vec.y = JUMP_POWER;
			setVec( vec );
			return;
		}
	}
	//浮いている
	if ( !isStanding( ) ) {
		setAction( ACTION_WAIT );
		return;
	}
	//ブレーキ
	if ( player.device_x == 0 &&
		 player.device_y == 0 ) {
		setAction( ACTION_BRAKE );
		return;
	}

	//移動
	Vector vec = Vector( player.device_x, 0, player.device_y ).normalize( ) * MOVE_SPEED;
	vec.y = getVec( ).y;
	setVec( vec );
}

void RockPlayer::actOnBraking( ) {
	//水平方向のベクトル
	Vector vec = getVec( );
	double tmp_y = vec.y;
	vec.y = 0;
	//ベクトルがない場合待機に移行する
	if ( vec.getLength( ) < 0.001 ) {
		setAction( ACTION_WAIT );
		return;
	}

	//減速処理
	if ( vec.getLength( ) > BRAKE_SPEED ) {
		vec -= vec.normalize( ) * BRAKE_SPEED;
	} else {
		vec = Vector( );
	}

	//垂直方向のベクトルを戻す
	vec.y = tmp_y;

	setVec( vec );
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
	case ACTION_WALK:
		anim_time = ( double )getActCount( ) * ANIM_SPEED;
		break;
	default:
		anim_time = 0;
		break;
	}
	return anim_time;
}

void RockPlayer::bound( ) {
	Vector vec = getVec( );
	vec.y = BOUND_POWER;
	setVec( vec );
	setAction( ACTION_JUMP );
}

bool RockPlayer::isOnHead( RockEnemyConstPtr target ) const {
	Vector vec = getVec( );
	if ( vec.y >= 0 ) {
		return false;
	}
	if ( !target->isHead( ) ) {
		return false;
	}
	Vector pos = getPos( );
	Vector target_pos = target->getPos( );
	double length = ( target_pos - pos ).getLength2( );
	if ( length < 1 ) {
		// 自分だったら判定しない
		return false;
	}
	if ( length > COLLISION_RANGE * COLLISION_RANGE ) {
		// 離れていたら判定しない
		return false;
	}
		
	double range = target->getRadius( ) + getRadius( );
	{//上下判定
		Vector diff = target_pos - ( pos + Vector( 0, vec.y, 0 ) );
		if ( diff.getLength2( ) > range * range ) {
			return false;
		}
	}
	return true;
}

void RockPlayer::damage( int force ) {
	setPos( getPos( ) - getVec( ) );
	MessageSender::getTask( )->sendMessage( _id, Message::COMMAND_POWER, &force );
}
