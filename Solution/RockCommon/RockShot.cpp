#include "RockShot.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "Effect.h"
#include "RockArmoury.h"


RockShot::RockShot( const Vector& pos, const Vector& dir, const int power ) :
RockCharacter( pos, DOLL_NONE, 32, 32, false, false, false ),
_finished( false ),
_power( power ),
_size( 1.0 ),
_effect_handle( -1 ) {
}

RockShot::~RockShot( ) {
}

bool RockShot::isFinished( ) const {
	return _finished;
}

void RockShot::setFinished( ) {
	_finished = true;
}

int RockShot::getPower( ) {
	return _power;
}

void RockShot::setSize( double size ) {
	_size = size;
}

void RockShot::setEffectHandle( int effect_handle ) {
	_effect_handle = effect_handle;
}

double RockShot::getSize( ) {
	return _size;
}

int RockShot::getEffectHandle( ) { 
	return _effect_handle;
}
void RockShot::setPower( int power ) {
	_power = power;
}