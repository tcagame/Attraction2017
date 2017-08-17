#include "RockImpact.h"

const int EFFECT_TIEM = 240;

RockImpact::RockImpact( const Vector& pos, double size ) :
_pos( pos ),
_size( size ),
_count( 0 ),
_finished( false ) {
}


RockImpact::~RockImpact( ) {
}

void RockImpact::update( ) {
	_count++;
	if ( _count > EFFECT_TIEM ) {
		_finished = true;
	}
}

Vector RockImpact::getPos( ) const {
	return _pos;
}

double RockImpact::getSize( ) const {
	return _size;
}

bool RockImpact::isFinished( ) const {
	return _finished;
}
