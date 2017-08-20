#include "EnemyEyeDaemon.h"

static const int WAIT_ANIM_TIME = 5;
static const int MAX_HP = 2;
const int MOVE_SPEED = 1;
const int JUMP_COUNT = 6;

EnemyEyeDaemon::EnemyEyeDaemon( const Vector& pos ) :
Enemy( pos, SMALL_CHAR_GRAPH_SIZE, MAX_HP ),
_before_pos( pos ),
_air_jump( false ) {
	setRadius( 16 );
}


EnemyEyeDaemon::~EnemyEyeDaemon( ) {
}

void EnemyEyeDaemon::act( ) {
	if ( _before_pos.x == getPos( ).x ) {
		if ( getDir( ) == DIR_LEFT ) {
			setVec( Vector( MOVE_SPEED, 0 ) );
		} else {
			setVec( Vector( -MOVE_SPEED, 0 ) );
		}
	}
	if ( getActCount( ) % JUMP_COUNT == 0 && isStanding( ) ) {
		Vector vec = getVec( );
		vec.y -= 12;
		setVec( vec );
	}
	if ( !_air_jump && getVec( ).y > 0 ) {
		_air_jump = true;
		Vector vec( getVec( ) );
		vec.y -= 12;
		setVec( vec );
	}
	if ( isStanding( ) ) {
		_air_jump = false;
	}

	_before_pos = getPos( );
}

Chip EnemyEyeDaemon::getChip( ) const {
	const int ANIM[ ] = {
		2, 3, 4, 5
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