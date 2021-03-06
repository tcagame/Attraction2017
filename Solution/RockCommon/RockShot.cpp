#include "RockShot.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "Effect.h"
#include "RockArmoury.h"


RockShot::RockShot( const Vector& pos, const Vector& dir, const int power ) :
RockCharacter( pos, DOLL_NONE, 32, 0, false, false, false, false ),
_finished( false ),
_power( power ),
_size( 1.0 ),
_effect_handle( -1 ) {
}

RockShot::~RockShot( ) {
	stopEffect( );
}

bool RockShot::isFinished( ) const {
	return _finished;
}

void RockShot::setFinished( ) {
	_finished = true;
}

int RockShot::getPower( ) const {
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

int RockShot::getEffectHandle( ) const { 
	return _effect_handle;
}
void RockShot::setPower( int power ) {
	_power = power;
}

void RockShot::stopEffect( ) {
	//エラー防止のため、故意に削除するときのみ外部からエフェクトストップ
	Effect::getTask( )->stopEffect( _effect_handle );
}
