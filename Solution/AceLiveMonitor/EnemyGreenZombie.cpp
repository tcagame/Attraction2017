#include "EnemyGreenZombie.h"

static const int WAIT_ANIM_TIME = 5;
static const int MOVE_SPEED = 5;
static const int JUMP_POWER = -50;

EnemyGreenZombie::EnemyGreenZombie( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE ),
_before_pos( Vector( ) ),
_vec( Vector( MOVE_SPEED, 0 ) ),
_jump_count( 1 ) {
	setRadius( 36 );
}


EnemyGreenZombie::~EnemyGreenZombie( ) {
}

void EnemyGreenZombie::act( ) {
	_jump_count++;
	if ( _before_pos.x == getPos( ).x ) {
		_vec.x *= -1;
		if ( isStanding( ) && _jump_count % 30 == 0 ) {
			_vec.y += JUMP_POWER;
		}
		setVec( _vec );
	}
	_before_pos = getPos( );
}

Chip EnemyGreenZombie::getChip( ) const {
	const int ANIM[ ] = {
		6, 7, 8, 9, 10, 11
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	Chip chip = Chip( );
	chip.tx = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] * 64;
	chip.ty = 3 * 64;
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