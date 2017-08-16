#include "EnemyCrocoSnake.h"

static const int WAIT_ANIM_TIME = 5;
static const int MOVE_SPEED = 1;
static const int POWER = 3;

EnemyCrocoSnake::EnemyCrocoSnake( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, POWER ),
_before_pos( Vector( ) ),
_vec( Vector( MOVE_SPEED, 0 ) ) {
	setRadius( 30 );
}


EnemyCrocoSnake::~EnemyCrocoSnake( ) {
}

void EnemyCrocoSnake::act( ) {
	if ( _before_pos.x == getPos( ).x ) {
		_vec.x *= -1;
		setVec( _vec );
	}
	_before_pos = getPos( );
}

Chip EnemyCrocoSnake::getChip( ) const {
	const int ANIM[ ] = {
		0, 1, 2, 3, 4, 5, 4, 3, 2, 1
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	Chip chip = Chip( );
	chip.tx = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] * 64;
	chip.ty = 8 * 64;
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
