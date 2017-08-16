#include "EnemyWhiteMist.h"

static const int WAIT_ANIM_TIME = 5;
static const int MOVE_SPEED = 2;
static const int FLOAT_RANGE = 10;
static const int MAX_HP = 3;

EnemyWhiteMist::EnemyWhiteMist( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP, false ),
_vy( 0 ),
_dir( 1 ) {
	setRadius( 36 );
}


EnemyWhiteMist::~EnemyWhiteMist( ) {
}

void EnemyWhiteMist::act( ) {
	_vy += _dir;
	setVec( Vector( -MOVE_SPEED, _vy ) );

	if ( _vy < -FLOAT_RANGE ) {
		_dir = 1;
	}
	if ( _vy > FLOAT_RANGE ) {
		_dir = -1;
	}
}

Chip EnemyWhiteMist::getChip( ) const {
	const int ANIM[ ] = {
		5, 6, 7, 8, 9, 10, 9, 8, 7, 6
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	Chip chip = Chip( );
	chip.tx = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] * 64;
	chip.ty = 7 * 64;
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