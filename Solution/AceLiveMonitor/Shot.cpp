#include "Shot.h"

const int SHOT_SPEED = 10; 
const int VANISH_LENGTH = 500;

Shot::Shot( const Vector& pos, DIR dir, int power ) :
Character( pos, NORMAL_CHAR_GRAPH_SIZE, false ),
_dir( dir ),
_pos( pos ),
_power( power ) {
	Vector vec = Vector( SHOT_SPEED, 0 );
	if ( dir == DIR_LEFT ) {
		vec.x *= -1;
	}
	setVec( vec );
}

Shot::~Shot( ) {
}

void Shot::act( ) {
}

void Shot::update( ) {
	_pos += getVec( );
	setPos( _pos );
}

DIR Shot::getDir( ) const {
	return _dir;
}

int Shot::getPower( ) const {
	return _power;
}

bool Shot::isFinish( ) const {
	return ( getActCount( ) * getVec( ).getLength( ) > VANISH_LENGTH );
}

Chip Shot::getChip( ) const {
	Vector pos = getPos( );
	Chip chip = Chip( );
	chip.tx = 0 + ( _power - 1 ) * 128 + 64 * ( getActCount( ) % 2 );
	chip.ty = 128;
	chip.size = getChipSize( );
	chip.sx1 = ( int )pos.x - chip.size / 2;
	chip.sx2 = chip.sx1 + chip.size;
	chip.sy1 = ( int )pos.y - chip.size;
	chip.sy2 = chip.sy1 + chip.size;
	if ( getDir( ) == DIR_RIGHT ) {
		int tmp = chip.sx1;
		chip.sx1 = chip.sx2;
		chip.sx2 = tmp;
	}
	return chip;
}