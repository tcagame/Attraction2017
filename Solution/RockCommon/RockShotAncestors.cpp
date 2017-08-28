#include "RockShotAncestors.h"
#include "Effect.h"
#include "RockArmoury.h"
#include "RockStudio.h"

const double MOVE_SPEED = 15;
const double EFFECT_SIZE = 6.0;
const int EXISTANCE_TIME = 400;

RockShotAncestors::RockShotAncestors( const int id, const Vector& pos, const Vector& dir, const int power ) :
RockShot( pos, dir, power ),
_target_id( id ) {
	setVec( dir * MOVE_SPEED );
	EffectPtr effect = Effect::getTask( );
	RockArmouryPtr armoury = RockArmoury::getTask( );

	setSize( EFFECT_SIZE );
	setEffectHandle( effect->playEffect( RockStudio::getTask( )->getEffectHandle( EFFECT_ANCESTORS_SHOT ) ) );

	double angle = Vector( 0, 0, -1 ).angle( dir );
	if ( Vector( 0, 0, -1 ).cross( dir ).y < 0 ) {
		angle *= -1;
	}
	Vector rotate = Vector( 0, angle, 0 );
	effect->updateEffectTransform( getEffectHandle( ), getPos( ), getSize( ), rotate );
}


RockShotAncestors::~RockShotAncestors( ) {
}

void RockShotAncestors::act( ) {
	if ( getActCount( ) > EXISTANCE_TIME ) {
		setFinished( );
		return;
	}
	double angle = Vector( 0, 0, -1 ).angle( getDir( ) );
	if ( Vector( 0, 0, -1 ).cross( getDir( ) ).y < 0 ) {
		angle *= -1;
	}
	Vector rotate = Vector( 0, angle, 0 );
	Effect::getTask( )->updateEffectTransform( getEffectHandle( ), getPos( ), getSize( ), rotate );
}
