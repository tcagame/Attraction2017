#include "EnemyMoth.h"

static const int WAIT_ANIM_TIME = 5;
static const int FLOAT_RANGE = 4;
static const int MAX_HP = 2;

EnemyMoth::EnemyMoth( const Vector& pos ) :
Enemy( pos, SMALL_CHAR_GRAPH_SIZE, MAX_HP, false ),
_vy( 0 ),
_dir( 1 ) {
	setRadius( 16 );
}


EnemyMoth::~EnemyMoth( ) {
}

void EnemyMoth::act( ) {
	_vy += _dir;
	setVec( Vector( 0, _vy ) );

	if ( _vy < -FLOAT_RANGE ) {
		_dir = 1;
	}
	if ( _vy > FLOAT_RANGE ) {
		_dir = -1;
	}
}

Chip EnemyMoth::getChip( ) const {
	const int ANIM[ ] = {
		0, 1
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	Chip chip = Chip( );
	chip.tx = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] * 32;
	chip.ty = 5 * 32;
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