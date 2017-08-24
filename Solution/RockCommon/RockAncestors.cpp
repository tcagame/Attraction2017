#include "RockAncestors.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockDollHouse.h"

static const int EXISTANCE_TIME = 2000;
static const double POP_Y = 1000;
static const double FOLLOW_RANGE = 70;
static const double FOLLOW_Y = 40;
static const double MOVE_SPEED = 30;

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
	Vector pop_pos = player_pos - player->getDir( ).normalize( ) * FOLLOW_RANGE;
	pop_pos.y = player_pos.y + POP_Y;
	setPos( pop_pos );
}

void RockAncestors::actOnAbsent( ) {
}

void RockAncestors::actOnFadeIn( ) {
	RockPlayerPtr player = RockFamily::getTask( )->getPlayer( _player_id );
	Vector player_pos = player->getPos( );
	Vector pos = getPos( );
	Vector target = player_pos - player->getDir( ).normalize( ) * FOLLOW_RANGE;
	target.y = player_pos.y + FOLLOW_Y;
	Vector distance = target - pos;
	if ( distance.getLength2( ) < 1 ) {
		setVec( distance );
		_action = ACTION_FOLLOW;
		return;
	}
	Vector vec = distance;
	if ( distance.getLength2( ) > MOVE_SPEED * MOVE_SPEED ) {
		vec = vec.normalize( ) * MOVE_SPEED;
	}
	setVec( vec );
}

void RockAncestors::actOnFollow( ) {
	if ( getActCount( ) > EXISTANCE_TIME ) {
		_action = ACTION_FADEOUT;
		return;
	}
	RockPlayerPtr player = RockFamily::getTask( )->getPlayer( _player_id );
	Vector player_pos = player->getPos( );
	Vector pos = getPos( );
	Vector distance = player_pos - pos;
	distance.y = 0;
	Vector vec = Vector( );
	if ( distance.getLength2( ) > FOLLOW_RANGE * FOLLOW_RANGE ) {
		//”ÍˆÍŠO‚É‚¢‚½‚ç”ÍˆÍ‚É“ü‚ë‚¤‚Æ‚·‚é
		Vector target = player_pos - distance.normalize( ) * FOLLOW_RANGE;
		target.y = player_pos.y + FOLLOW_Y;
		vec = target - pos;
		if ( vec.getLength2( ) > MOVE_SPEED * MOVE_SPEED ) {
			vec = vec.normalize( ) * MOVE_SPEED * MOVE_SPEED;
		}
	}
	setVec( vec );
}

void RockAncestors::actOnFadeOut( ) {
	if ( getPos( ).y > RockFamily::getTask( )->getPlayer( _player_id )->getPos( ).y + POP_Y ) {
		setVec( Vector( ) );
		_action = ACTION_ABSENT;
		return;
	}
	setVec( Vector( 0, MOVE_SPEED, 0 ) );
}


ModelMV1Ptr RockAncestors::getModel( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	
	double rot = Vector( 0, 0, -1 ).angle( getDir( ) );
	Vector axis = Vector( 0, 1, 0 );
	if ( Vector( 0, 0, -1 ).cross( getDir( ) ).y < 0 ) {
		axis = Vector( 0, -1, 0 );
	}
	model->setRot( Matrix::makeTransformRotation( axis, rot ) );
	model->setTrans( Matrix::makeTransformTranslation( getPos( ) ) );
	return model;
}
