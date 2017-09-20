#include "RockAncestors.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockDollHouse.h"
#include "RockArmoury.h"
#include "RockShotAncestors.h"
#include "Sound.h"
#include "RockStudio.h"
#include "Effect.h"

static const int EXISTANCE_TIME = 2000;
//pop
static const Vector POP_POS( 0, 500, -500 );//プレイヤーの向きにあわせる( zが奥行き )
static const Vector TARGET( 0, 40, 100 );//プレイヤーの向きにあわせる( zが奥行き )
//追従
static const double FOLLOW_RANGE = 50;
static const double FOLLOW_Y = 30;
//移動
static const double MAX_MOVE_SPEED = 5.55;
static const double ACCEL = 1.11;
//しょっと
static const int SHOT_INTERVAL = 50;
static const int SHOT_POWER = 3;
static const double SHOT_ANGLE = PI / 6;
static const Vector SHOT_FOOT( 0, 0, 0 );//ショットの高さ
//アニメーション
static const double ANIM_SPEED = 1.0;

RockAncestors::RockAncestors( int id ) :
RockCharacter( Vector( ), DOLL_ANCESTORS, 30, 50, false, false, false ),
_player_id( id ),
_action( ACTION_ABSENT ) {

}


RockAncestors::~RockAncestors( ) {
}

bool RockAncestors::isActive( ) {
	return _action != ACTION_ABSENT;
}

void RockAncestors::act( ) {
	switch ( _action ) {
	case ACTION_ABSENT:
		actOnAbsent( );
		break;
	case ACTION_FADEIN:
		actOnFadeIn( );
		break;
	case ACTION_FADEOUT:
		actOnFadeOut( );
		break;
	case ACTION_FOLLOW:
		actOnFollow( );
		break;
	}
}

void RockAncestors::pop( ) {
	_action = ACTION_FADEIN;
	RockPlayerPtr player = RockFamily::getTask( )->getPlayer( _player_id );
	Vector player_pos = player->getPos( );
	Vector player_dir = player->getDir( );
	double angle = Vector( 0, 0, -1 ).angle( player_dir );
	Vector axis = Vector( 0, 0, -1 ).cross( player_dir );
	if ( axis.y > 0 ) {
		axis = Vector( 0, -1, 0 );
	} else {
		axis = Vector( 0, 1, 0 );
	}
	Vector pop_relative_pos = Matrix::makeTransformRotation( axis, angle ).multiply( POP_POS );
	Vector pop_pos = player_pos + pop_relative_pos;
	setPos( pop_pos );
	
	EffectPtr effect( Effect::getTask( ) );
	_fadein_effect = effect->playEffect( RockStudio::getTask( )->getEffectHandle( EFFECT_ANCESTORS_FADEIN ) );
	effect->updateEffectTransform( _fadein_effect, getPos( ), 5 );
}

void RockAncestors::actOnAbsent( ) {
}

void RockAncestors::actOnFadeIn( ) {
	//プレイヤーの後ろを目指す
	RockPlayerPtr player = RockFamily::getTask( )->getPlayer( _player_id );
	Vector player_pos = player->getPos( );
	Vector player_dir = player->getDir( );
	double angle = Vector( 0, 0, -1 ).angle( player_dir );
	Vector axis = Vector( 0, 0, -1 ).cross( player_dir );
	if ( axis.y > 0 ) {
		axis = Vector( 0, -1, 0 );
	} else {
		axis = Vector( 0, 1, 0 );
	}

	Vector relative_target = Matrix::makeTransformRotation( axis, angle ).multiply( TARGET );
	Vector target = player_pos + relative_target;

	Vector distance = target - getPos( );
	if ( distance.getLength2( ) < 30 ) {
		_action = ACTION_FOLLOW;
		EffectPtr effect( Effect::getTask( ) );
		int handle = effect->playEffect( RockStudio::getTask( )->getEffectHandle( EFFECT_ANCESTORS_POP ) );
		effect->updateEffectTransform( handle, getPos( ), 10 );
		setActCount( 0 );
		return;
	}
	Vector vec = getVec( ) + distance.normalize( ) * ACCEL;
	if ( vec.getLength2( ) > MAX_MOVE_SPEED * MAX_MOVE_SPEED ) {
		vec = vec.normalize( ) * MAX_MOVE_SPEED;
	}
	
	setVec( vec );
	
	Effect::getTask( )->updateEffectTransform( _fadein_effect, getPos( ), 5 );
}

void RockAncestors::actOnFollow( ) {
	if ( getActCount( ) > EXISTANCE_TIME ) {
		_action = ACTION_FADEOUT;
		return;
	}
	RockPlayerPtr player = RockFamily::getTask( )->getPlayer( _player_id );
	const Vector player_pos = player->getPos( );
	Vector player_dir = player->getDir( ).normalize( );
	player_dir.y = 0;
	Vector vec = Vector( );
	Vector target = player_pos - ( player_dir * FOLLOW_RANGE );
	target.y = FOLLOW_Y + player_pos.y;
	Vector distance_to_target = target - getPos( );
	if ( distance_to_target.getLength2( ) > ACCEL * ACCEL ) {
		vec = getVec( ) + distance_to_target.normalize( ) * ACCEL;
	}
	if ( vec.getLength2( ) < MAX_MOVE_SPEED * MAX_MOVE_SPEED ) {
		vec = distance_to_target;
	}
	if ( vec.getLength2( ) > MAX_MOVE_SPEED * MAX_MOVE_SPEED ) {
		vec = vec.normalize( ) * MAX_MOVE_SPEED;
	}
	if ( vec.angle( distance_to_target ) > PI / 2 ) {
		vec -= vec.normalize( ) * ACCEL;
	}
	setVec( vec );
	{ // 向いている方向の修正
		Vector dir = getVec( ).normalize( );
		Vector distance = player_pos - getPos( );
		if ( dir.isOrijin( ) ||
			 distance.getLength2( ) < FOLLOW_RANGE * FOLLOW_RANGE ) {
			dir = ( player_pos - getPos( ) ).normalize( );
		}
		dir.y = 0;
		setDir( dir );
	}

	//一定時間ごとにショットを打つ
	if ( getActCount( ) % SHOT_INTERVAL == 0 ) {
		Sound::getTask( )->playSE( "yokai_se_27.wav" );
		RockArmouryPtr armoury = RockArmoury::getTask( );
		Vector dir = getDir( );

		Vector pos = getPos( ) + SHOT_FOOT;
		Matrix left_rot = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), SHOT_ANGLE );
		Matrix right_rot = Matrix::makeTransformRotation( Vector( 0, -1, 0 ), SHOT_ANGLE );
		armoury->addShot( RockShotPtr( new RockShotAncestors( _player_id, pos, dir						, SHOT_POWER ) ) );
		armoury->addShot( RockShotPtr( new RockShotAncestors( _player_id, pos, left_rot.multiply( dir )	, SHOT_POWER ) ) );
		armoury->addShot( RockShotPtr( new RockShotAncestors( _player_id, pos, right_rot.multiply( dir ), SHOT_POWER ) ) );
	}
}

void RockAncestors::actOnFadeOut( ) {
	if ( getPos( ).y > RockFamily::getTask( )->getPlayer( _player_id )->getPos( ).y + POP_POS.y ) {
		setVec( Vector( ) );
		_action = ACTION_ABSENT;
		return;
	}
	setVec( Vector( 0, MAX_MOVE_SPEED, 0 ) );
}


ModelMV1Ptr RockAncestors::getModel( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	Vector dir = getDir( );
	double rot = Vector( 0, 0, -1 ).angle( dir );
	Vector axis = Vector( 0, 1, 0 );
	if ( Vector( 0, 0, -1 ).cross( dir ).y < 0 ) {
		axis = Vector( 0, -1, 0 );
	}
	model->setRot( Matrix::makeTransformRotation( axis, rot ) );
	model->setTrans( Matrix::makeTransformTranslation( getPos( ) ) );
	model->setAnimTime( fmod( ( double )getActCount( ) * ANIM_SPEED, model->getEndAnimTime( ) ) );
	return model;
}


void RockAncestors::resetPos( ) {
	RockPlayerPtr player = RockFamily::getTask( )->getPlayer( _player_id );
	Vector player_dir = player->getDir( ).normalize( );
	player_dir.y = 0;
	Vector player_pos = player->getPos( );
	Vector target = player_pos - ( player_dir * FOLLOW_RANGE );
	target.y = FOLLOW_Y + player_pos.y;
	setPos( target );
}
