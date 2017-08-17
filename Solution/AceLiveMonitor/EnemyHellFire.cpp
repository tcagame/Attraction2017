#include "EnemyHellFire.h"
#include "Family.h"

static const int HP = 3;
static const double MOVE_SPEED = 3;
static const double ACCEL = 0.5;
static const int WAIT_ANIM_TIME = 5;

EnemyHellFire::EnemyHellFire( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, HP, false ) {
	setVec( Vector( MOVE_SPEED, 0 ) );
}


EnemyHellFire::~EnemyHellFire( ) {
}

void EnemyHellFire::act( ) {
	Vector target = Vector( Family::getTask( )->getCameraPos( ) + GRAPH_SIZE, GRAPH_SIZE / 2 );
	Vector distance = target - getPos( );
	Vector vec = getVec( ) + distance.normalize( ) * ACCEL;
	vec = vec.normalize( ) * MOVE_SPEED;
	setVec( vec );
}

Chip EnemyHellFire::getChip( ) const {
	const int ANIM[ ] = {
		 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
		10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	Chip chip = Chip( );
	chip.tx = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] * 64;
	chip.ty = 16 * 64;
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