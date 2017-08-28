#include "RockShotPlayer.h"
#include "RockArmoury.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "Effect.h"
#include "RockStudio.h"

const int MOVE_SPEED = 3;
const double EFFECT_NORMAL_SIZE = 10.0;
const double EFFECT_CHARGE_SIZE = 5.0;
const int ACTIVE_COUNT = 150;

RockShotPlayer::RockShotPlayer( const int id, const Vector& pos, const Vector& dir, const int power ) :
RockShot( pos, dir, power ),
_back( false ),
_target_id( id ) {
	setVec( dir * MOVE_SPEED );
	EffectPtr effect = Effect::getTask( );
	RockStudioPtr studio = RockStudio::getTask( );

	if ( power == MAX_PLAYER_SHOT_POWER ) {
		setSize( EFFECT_CHARGE_SIZE );
		setEffectHandle( effect->playEffect( studio->getEffectHandle( EFFECT_CHARGE_SHOT ) ) );
	} else {
		setSize( EFFECT_NORMAL_SIZE );
		setEffectHandle( effect->playEffect( studio->getEffectHandle( EFFECT_SHOT ) ) );
	}


	double angle = Vector( 0, 0, -1 ).angle( dir );
	if ( Vector( 0, 0, -1 ).cross( dir ).y < 0 ) {
		angle *= -1;
	}
	Vector rotate = Vector( 0, angle, 0 );
	effect->updateEffectTransform( getEffectHandle( ), getPos( ), getSize( ), rotate );
}


RockShotPlayer::~RockShotPlayer( ) {
}

void RockShotPlayer::act( ) {
	double angle = Vector( 0, 0, -1 ).angle( getDir( ) );
	if ( Vector( 0, 0, -1 ).cross( getDir( ) ).y < 0 ) {
		angle *= -1;
	}
	Vector rotate = Vector( 0, angle, 0 );
	Effect::getTask( )->updateEffectTransform( getEffectHandle( ), getPos( ), getSize( ), rotate );
	if ( getActCount( ) > ACTIVE_COUNT ) {
		_back = true;
	}
	if ( _back ) {
		actOutBack( );
	}
}

void RockShotPlayer::actOutBack( ) {
	RockPlayerPtr player = RockFamily::getTask( )->getPlayer( _target_id );
	Vector diff = ( player->getPos( ) + Vector( 0, getRadius( ), 0 ) - getPos( ) );
	if ( diff.getLength2( ) > MOVE_SPEED * MOVE_SPEED ) {
		setVec( diff.normalize( ) * MOVE_SPEED );
	} else {
		Effect::getTask( )->stopEffect( getEffectHandle( ) );
		setFinished( );
	}
}

void RockShotPlayer::setBack( ) {
	_back = true;
}