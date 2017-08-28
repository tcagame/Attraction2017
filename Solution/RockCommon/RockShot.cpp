#include "RockShot.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "Effect.h"
#include "RockArmoury.h"

const int ACTIVE_COUNT = 150;
const int MOVE_SPEED = 3;
const Vector FOOT( 0, 35, 0 ); // ƒvƒŒƒCƒ„[‚Ì‘«Œ³‚©‚ç‚Ì‚‚³
const double EFFECT_SIZE = 10.0;

RockShot::RockShot( const int id_, const Vector& pos, const Vector& dir, const int power ) :
RockCharacter( pos + FOOT, DOLL_NONE, 32, 32, false, false, false ),
_player_id( id_ ),
_back( false ),
_finished( false ),
_power( power ) {
	setVec( dir * MOVE_SPEED );
	_effect_handle = Effect::getTask( )->playEffect( RockArmoury::getTask( )->getEffectShotId( ) );
	double angle = Vector( 0, 0, -1 ).angle( dir );
	if ( Vector( 0, 0, -1 ).cross( dir ).y < 0 ) {
		angle *= -1;
	}
	Effect::getTask( )->updateEffectTransform( _effect_handle, pos + FOOT, EFFECT_SIZE, Vector( 0, angle, 0 ) );
}

RockShot::~RockShot( ) {
}

void RockShot::act( ) {
	double angle = Vector( 0, 0, -1 ).angle( getDir( ) );
	if ( Vector( 0, 0, -1 ).cross( getDir( ) ).y < 0 ) {
		angle *= -1;
	}
	Effect::getTask( )->updateEffectTransform( _effect_handle, getPos( ), EFFECT_SIZE, Vector( 0, angle, 0 ) );
	if ( getActCount( ) > ACTIVE_COUNT ) {
		_back = true;
	}
	if ( _back ) {
		actOutBack( );
	}
}

void RockShot::actOutBack( ) {
	RockPlayerPtr player = RockFamily::getTask( )->getPlayer( _player_id );
	Vector diff = ( player->getPos( ) + FOOT - getPos( ) );
	if ( diff.getLength2( ) > MOVE_SPEED * MOVE_SPEED ) {
		setVec( diff.normalize( ) * MOVE_SPEED );
	} else {
		Effect::getTask( )->stopEffect( _effect_handle );
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

