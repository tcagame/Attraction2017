#include "EnemyPurpleZombie.h"
#include "ace_define.h"

static const int WAIT_ANIM_TIME = 5;
static const int MOVE_SPEED = 4;
static const int MAX_HP = 3;

EnemyPurpleZombie::EnemyPurpleZombie( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP ),
_before_pos( Vector( ) ),
_vec( Vector( -MOVE_SPEED, 0 ) ) {
	setRadius( 36 );
}


EnemyPurpleZombie::~EnemyPurpleZombie( ) {
}

void EnemyPurpleZombie::act( ) {
	if ( _before_pos.x == getPos( ).x ) {
		_vec.x *= -1;
		setVec( _vec );
	}
	_before_pos = getPos( );
}

Chip EnemyPurpleZombie::getChip( ) const {
	const int ANIM[ ] = {
		0, 1, 2, 3, 4, 5
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	int cx = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ];
	int cy = 3;

	Chip chip = Chip( );
	chip.size = getChipSize( );
	chip.tx = cx * 64;
	chip.ty = cy * 64;

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