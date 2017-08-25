#include "RockShot.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "Effect.h"
#include "RockArmoury.h"

const int ACTIVE_COUNT = 150;
const int MOVE_SPEED = 3;
const Vector FOOT( 0, 30, 0 ); // プレイヤーの足元からの高さ

RockShot::RockShot( const int id_, const Vector& pos, const Vector& dir, const int power ) :
RockCharacter( pos + FOOT, DOLL_NONE, 32, 32, false, false ),
_player_id( id_ ),
_back( false ),
_finished( false ),
_power( power ) {
	setVec( dir * MOVE_SPEED );
	_effect_handle = Effect::getTask( )->playEffect( RockArmoury::getTask( )->getEffectShotId( ) );
	Effect::getTask( )->updateEffectTransform( _effect_handle, pos + FOOT );
}

RockShot::~RockShot( ) {
}

void RockShot::act( ) {
	Effect::getTask( )->updateEffectTransform( _effect_handle, getPos( ) + FOOT );
	if ( getActCount( ) > ACTIVE_COUNT ) {
		_back = true;
	}
	if ( _back ) {
		actOutBack( );
	}
}

void RockShot::actOutBack( ) {
	RockPlayerPtr player = RockFamily::getTask( )->getPlayer( _player_id );
	Vector diff = ( ( player->getPos( ) + FOOT ) - getPos( ) );
	if ( diff.getLength2( ) > 1 ) {
		setVec( diff.normalize( ) * MOVE_SPEED );
	} else {
		_finished = true;
	}
}

double RockShot::getAnimTime( ) const {
	return 0;
}

bool RockShot::isFinished( ) const {
	return _finished;
}

bool RockShot::isBack( ) const {
	return _back;
}

void RockShot::setFinished( ) {
	_finished = true;
}

void RockShot::setBack( ) {
	_back = true;
}

ModelMV1Ptr RockShot::getModel( ) const {
	return ModelMV1Ptr( );
}

int RockShot::getPower( ) {
	return _power;
}

