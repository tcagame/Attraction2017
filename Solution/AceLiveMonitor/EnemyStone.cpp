#include "EnemyStone.h"

static const int WAIT_ANIM_TIME = 5;
static const int MOVE_SPEED = 5;
static const int MAX_HP = 2;

EnemyStone::EnemyStone( const Vector& pos ) :
Enemy( pos, SMALL_CHAR_GRAPH_SIZE, MAX_HP ),
_before_pos( Vector( ) ),
_vec( Vector( -MOVE_SPEED, 2 ) ) {
	setRadius( 16 );
	setVec( _vec );
}


EnemyStone::~EnemyStone( ) {
}

void EnemyStone::act( ) {
	if ( _before_pos.x == getPos( ).x ) {
		_vec.x *= -1;
		setVec( _vec );
	}
	_before_pos = getPos( );
}

Chip EnemyStone::getChip( ) const {
	const int ANIM[ ] = {
		0, 1, 2, 3, 4, 5, 6, 7
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	Chip chip = Chip( );
	chip.tx = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] * 32;
	chip.ty = 6 * 32;
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