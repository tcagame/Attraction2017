#include "RockPlayer.h"
#include "RockClientInfo.h"
#include "RockFamily.h"
#include "RockEnemy.h"
#include "RockMilitary.h"
#include "RockCamera.h"
#include "RockCharacter.h"
#include "RockArmoury.h"
#include "RockShot.h"
#include "RockDollHouse.h"
#include "RockAncestors.h"
#include "Status.h"
#include "Device.h"
#include "Drawer.h"
#include "MessageSender.h"
#include "Effect.h"
#include "RockShotPlayer.h"
#include "RockStudio.h"


//移動
static const double JUMP_POWER = 6.0;
static const double MOVE_SPEED = 3.0;
static const double BRAKE_SPEED = 0.3;
//アニメーション
static const double ANIM_SPEED = 0.5;

static const int RADIUS = 10;
static const int HEIGHT = 20;

//チャージ時間
static const int CHARGE_PHASE_COUNT = 25;
static const int MAX_CHARGE_COUNT = CHARGE_PHASE_COUNT * 4 - 1;
//チャージエフェクト位置
static const Vector EFFECT_ADJUST( 0, 15, 0 );

//その他
static const int MAX_WISH_COUNT = 100;
static const int ENHANCED_POWER = 2;
static const Vector SHOT_FOOT( 0, 35, 0 );//ショットの高さ
static const Vector BUBBLE_SEARCH_RANGE = Vector( 1, 1, 1 ) * 3000.0;
static const double BUBBLE_FOLLOW_RANGE = 60.0;
static const Vector BUBBLE_FOOT = Vector( 0, 60, 0 );
static const double BUBBLE_MOVE_SPEED = MOVE_SPEED * 0.9;
static const int DEAD_ANIM_TIME = 150;


RockPlayer::RockPlayer( StatusPtr status, const Vector& pos, int id, RockAncestorsPtr ancestors ) :
RockCharacter( pos, ( DOLL )( DOLL_TAROSUKE_WAIT + id * ROCK_PLAYER_MOTION_NUM ), RADIUS, HEIGHT ),
_attack_count( 0 ),
_effect_handle( -1 ),
_ancestors( ancestors ) {
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
		break;
	case ACTION_CHARGE:
		actOnCharging( );
		break;
	case ACTION_DEAD:
		actOnDead( );
		break;
	case ACTION_WISH:
		actOnWish( );
		break;
	}
	actOnAttacking( );
	updateEffect( );
	// カメラに入り続ける
	DrawerPtr drawer( Drawer::getTask( ) );
	if ( !drawer->isInCamera( getPos( ) + getVec( ) ) ) {
		setVec( Vector( ) );
	}
	Vector dir = ( RockCamera::getTask( )->getTarget( ) - getPos( ) ).normalize( );
	while( !drawer->isInCamera( getPos( ) + getVec( ) ) ) {
		setVec( getVec( ) + dir );
	}
}

void RockPlayer::updateEffect( ) {
	EffectPtr effect( Effect::getTask( ) );
	int size = ( ( _attack_count / CHARGE_PHASE_COUNT ) * 2 ) + 4;
	effect->updateEffectTransform( _effect_handle, getPos( ) + EFFECT_ADJUST, size );
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
	case ACTION_DEAD:
		setDoll( ( DOLL )( DOLL_TAROSUKE_DEAD + _id * ROCK_PLAYER_MOTION_NUM ) );
		break;
	case ACTION_CHARGE:
		setDoll( ( DOLL )( DOLL_TAROSUKE_CHARGE + _id * ROCK_PLAYER_MOTION_NUM ) );
		break;
	case ACTION_WISH:
		setDoll( ( DOLL )( DOLL_TAROSUKE_WISH + _id * ROCK_PLAYER_MOTION_NUM ) );
		break;
	default:
		setDoll( ( DOLL )( DOLL_TAROSUKE_WAIT + _id * ROCK_PLAYER_MOTION_NUM ) );
		break;
	}
}

bool RockPlayer::isActive( ) const {
	return (  RockClientInfo::getTask( )->getClientId( ) == _status->getPlayer( _id ).area );
}

void RockPlayer::actOnWaiting( ) {
	Status::Player player = _status->getPlayer( _id );
	//死亡
	if ( player.power <= 0 ) {
		setAction( ACTION_DEAD );
		return;
	}
	//ジャンプ
	if ( isStanding( ) ) {
		if ( player.device_button & BUTTON_C ) {
			setAction( ACTION_JUMP );
			Vector vec = getVec( );
			vec.y = JUMP_POWER;
			setVec( vec );
			return;
		}
	}
	//攻撃
	if ( player.device_button & BUTTON_A ) {
		setAction( ACTION_CHARGE );
		return;
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
	//_attack_count -= 2;
}

void RockPlayer::actOnJumping( ) {
	Status::Player player = _status->getPlayer( _id );
	//死亡
	if ( player.power <= 0 ) {
		setAction( ACTION_DEAD );
		return;
	}
	if ( isStanding( ) ) {
	//攻撃
		if ( player.device_button & BUTTON_A ) {
			setAction( ACTION_CHARGE );
		} else {
			setAction( ACTION_WAIT );
		}
		return;
	}
	//移動
	Vector vec = Vector( player.device_x, 0, player.device_y ).normalize( ) * MOVE_SPEED;
	vec.y = getVec( ).y;
	setVec( vec );
}

void RockPlayer::actOnWalking( ) {
	Status::Player player = _status->getPlayer( _id );
	//死亡
	if ( player.power <= 0 ) {
		setAction( ACTION_DEAD );
		return;
	}
	//ジャンプ
	if ( isStanding( ) ) {
		if ( player.device_button & BUTTON_C ) {
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

void RockPlayer::actOnAttacking( ) {	
	Status::Player player = _status->getPlayer( _id );
	// 攻撃ボタンが離されたら攻撃
	if ( !( player.device_button & BUTTON_A ) &&
		 _attack_count > 0 ) {
		int power = _attack_count / ( MAX_CHARGE_COUNT / ( MAX_PLAYER_SHOT_POWER - 1 ) ) + 1;
		if ( player.item & ITEM_ENHANCED_ATTACK ) {
			power *= ENHANCED_POWER;
		}
		RockShotPtr shot( new RockShotPlayer( _id, getPos( ) + SHOT_FOOT, getDir( ), power ) );
		RockArmoury::getTask( )->addShot( shot );
		setAction( ACTION_WAIT );
		Effect::getTask( )->stopEffect( _effect_handle );
		_attack_count = 0;
		_effect_handle = -1;
	}
}

void RockPlayer::actOnCharging( ) {
	Status::Player player = _status->getPlayer( _id );
	//死亡
	if ( player.power <= 0 ) {
		setAction( ACTION_DEAD );
		_attack_count = 0;
		_effect_handle = -1;
		return;
	}
	// ジャンプ中であればチャージしない
	if ( !isStanding( ) ) {
		setAction( ACTION_WAIT );
		return;
	}

	if ( _attack_count == 0 ) {
		EffectPtr effect( Effect::getTask( ) );
		_effect_handle = effect->playEffect( RockStudio::getTask( )->getEffectHandle( EFFECT_CHARGE ) );
		effect->updateEffectTransform( _effect_handle, getPos( ) + EFFECT_ADJUST );
	}
	
	if ( player.item & ITEM_ENHANCED_CHARGE ) {
		_attack_count += 2;
	} else {
		_attack_count++;
	}
	if ( _attack_count > MAX_CHARGE_COUNT ) {
		_attack_count = MAX_CHARGE_COUNT;
	}

	//攻撃中の移動
	if ( player.device_x != 0 ||
		 player.device_y != 0 ) {
		setAction( ACTION_WALK );
		return;
	}
	if ( player.device_button & BUTTON_C ) {
		setAction( ACTION_JUMP );
		Vector vec( getVec( ) );
		vec.y = JUMP_POWER;
		setVec( vec );
		return;
	}
}

void RockPlayer::actOnBraking( ) {
	Status::Player player = _status->getPlayer( _id );
	//死亡
	if ( player.power <= 0 ) {
		setAction( ACTION_DEAD );
		return;
	}
	//水平方向のベクトル
	Vector vec = getVec( );
	double tmp_y = vec.y;
	vec.y = 0;
	//ベクトルがない場合は待機かチャージに移行する
	if ( vec.getLength( ) < 0.001 ) {
		if ( player.device_button & BUTTON_A ) {
			setAction( ACTION_CHARGE );
		} else {
			setAction( ACTION_WAIT );
		}
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

void RockPlayer::actOnDead( ) {
	if ( getActCount( ) < DEAD_ANIM_TIME ) {
		return;
	}
	RockFamilyPtr family = RockFamily::getTask( );
	Vector near_distance = BUBBLE_SEARCH_RANGE;
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		if ( _id == i ) {
			continue;
		}
		RockPlayerPtr player = family->getPlayer( i );
		if ( !player->isActive( ) ||
			 player->isDead( ) ) {
			continue;
		}
		Vector distance = player->getPos( ) + BUBBLE_FOOT - getPos( );
		if ( near_distance.getLength2( ) > distance.getLength2( ) &&
			 distance.getLength2( ) > BUBBLE_FOLLOW_RANGE * BUBBLE_FOLLOW_RANGE ) {
			near_distance = distance;
		}
	}
	if ( near_distance != BUBBLE_SEARCH_RANGE ) {
		Vector vec = near_distance;
		if ( vec.getLength2( ) > BUBBLE_MOVE_SPEED * BUBBLE_MOVE_SPEED ) {
			vec = vec.normalize( ) * BUBBLE_MOVE_SPEED;
		}
		setVec( vec );
	}
}

void RockPlayer::actOnWish( ) {
	if ( getActCount( ) > MAX_WISH_COUNT ) {
		setAction( ACTION_WAIT );
	}
}

ModelMV1Ptr RockPlayer::getModel( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	double anim_time = 0;
	double end_time = model->getEndAnimTime( );
	switch ( _action ) {
	case ACTION_WAIT:		
		anim_time = fmod( ( double )getActCount( ) * ANIM_SPEED, end_time );
		break;
	case ACTION_JUMP:
	{
		anim_time = ( double )getActCount( ) * ANIM_SPEED;
		if ( anim_time >= end_time ) {
			anim_time = end_time;
		}
	}
		break;
	case ACTION_WALK:
		anim_time = fmod( ( double )getActCount( ) * ANIM_SPEED, end_time );
		break;
	case ACTION_DEAD:
	{
		anim_time = ( double )getActCount( ) * ANIM_SPEED;
		if ( anim_time >= end_time ) {
			anim_time = end_time;
		}
	}
		break;
	case ACTION_CHARGE:
		anim_time = ( double )getActCount( ) * ANIM_SPEED;
		break;
	case ACTION_WISH:
		anim_time = fmod( ( double )getActCount( ) * ANIM_SPEED, end_time );
		break;
	default:
		anim_time = 0;
		break;
	}

	model->setAnimTime( anim_time );
	double rot = Vector( 0, 0, -1 ).angle( getDir( ) );
	Vector axis = Vector( 0, 1, 0 );
	if ( Vector( 0, 0, -1 ).cross( getDir( ) ).y < 0 ) {
		axis = Vector( 0, -1, 0 );
	}
	model->setRot( Matrix::makeTransformRotation( axis, rot ) );
	model->setTrans( Matrix::makeTransformTranslation( getPos( ) ) );
	return model;
}

void RockPlayer::damage( int force ) {
	MessageSender::getTask( )->sendMessage( _id, Message::COMMAND_POWER, &force );
}

void RockPlayer::bound( ) {
	RockCharacter::bound( );
	setAction( ACTION_JUMP );
}


void RockPlayer::back( ) {
	Vector vec = getVec( );
	setPos( getPos( ) - Vector( vec.x, 0, vec.z ) );
}

void RockPlayer::wish( ) {
	if ( !isStanding( ) ||
		 _action == ACTION_WISH ) {
		return;
	}
	setAction( ACTION_WISH );
	setVec( Vector( ) );
	_ancestors->pop( );
}

void RockPlayer::resetPos( const Vector& pos ) {
	setPos( pos );
}

bool RockPlayer::isDead( ) const {
	return _action == ACTION_DEAD;
}

