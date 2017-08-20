#include "EnemyNoFace.h"
#include "ace_define.h"

const int WAIT_ANIM_TIME = 5;
const int MAX_HP = 3;
const int MOVE_RANGE = 10;
const double MOVE_SPEED = 0.5;

EnemyNoFace::EnemyNoFace( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP ),
_vec_x( -MOVE_SPEED ) {
	setRadius( 36 );
	setVec( Vector( _vec_x, 0 ) );
}

EnemyNoFace::~EnemyNoFace( ) {
}

void EnemyNoFace::act( ) {
	Vector vec = getVec( );

	if ( vec.x < -MOVE_RANGE ) {
		_vec_x = MOVE_SPEED;
	}
	if ( vec.x > MOVE_RANGE ) {
		_vec_x = -MOVE_SPEED;
	}

	setVec( Vector( vec.x + _vec_x, vec.y ) );
}

Chip EnemyNoFace::getChip( ) const {
	const int ANIM[ ] = {
		0, 1, 2, 3, 4, 5, 6, 7, 6, 7, 6, 5, 4, 3, 2, 1
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	Chip chip = Chip( );
	chip.tx = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] * 64;
	chip.ty = 11 * 64;
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