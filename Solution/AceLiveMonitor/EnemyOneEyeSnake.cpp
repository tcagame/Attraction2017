#include "EnemyOneEyeSnake.h"

static const int WAIT_ANIM_TIME = 5;
static const int MOVE_SPEED = 2;
static const int MAX_HP = 3;
static const int JUMP_POWER = -400;

EnemyOneEyeSnake::EnemyOneEyeSnake( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP ),
_before_pos( Vector( ) ),
_vec( Vector( MOVE_SPEED, 0 ) ) {
	setRadius( 36 );
}


EnemyOneEyeSnake::~EnemyOneEyeSnake( ) {
}

void EnemyOneEyeSnake::act( ) {
	if ( _before_pos.x == getPos( ).x ) {
		_vec.x *= -1;
		setVec( _vec );
	}
	if ( isStanding( ) && getActCount( ) % 90 == 0 ) {
		_vec.y += JUMP_POWER;
		setVec( _vec );
	}
	_before_pos = getPos( );
}

Chip EnemyOneEyeSnake::getChip( ) const {
	const int ANIM[ ] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 10
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	Chip chip = Chip( );
	chip.tx = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] * 64;
	chip.ty = 0 * 64;
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
