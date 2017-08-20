#include "EnemyBat.h"

const int WAIT_ANIM_TIME = 3;
const int MAX_HP = 1;
const int MOVE_SPEED = 2;
const Vector POS( 10, 0 );

EnemyBat::EnemyBat( const Vector& pos ) :
Enemy( pos + POS, SMALL_CHAR_GRAPH_SIZE, MAX_HP, false ),
_center( pos ) {
	setRadius( 16 );
}


EnemyBat::~EnemyBat( ) {
}

void EnemyBat::act( ) {
	Vector radius = getPos( ) - _center;
	Matrix mat = Matrix::makeTransformRotation( Vector( 0, 0, -1 ), 1 / radius.getLength( ) );
	Vector f_pos = mat.multiply( radius );
	Vector rot = ( f_pos + _center ) - getPos( );
	setVec( rot * MOVE_SPEED );
}

Chip EnemyBat::getChip( ) const {
	const int ANIM[ ] = {
		3, 4, 5, 6
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	Chip chip = Chip( );
	chip.tx = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] * 32;
	chip.ty = 0 * 32;
	chip.size = getChipSize( );
	
	Vector pos = getPos( );
	DIR dir = getDir( );
	if ( dir == DIR_RIGHT ){
		chip.sx1 = ( int )pos.x - chip.size / 2 + chip.size;
		chip.sy1 = ( int )pos.y - chip.size;
		chip.sx2 = chip.sx1 - chip.size;
		chip.sy2 = chip.sy1 + chip.size;
	} else {
		chip.sx1 = ( int )pos.x - chip.size / 2;
		chip.sy1 = ( int )pos.y - chip.size;
		chip.sx2 = chip.sx1 + chip.size;
		chip.sy2 = chip.sy1 + chip.size;
	}
	return chip;
}