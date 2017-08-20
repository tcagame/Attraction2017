#include "EnemyHugDaemon.h"
#include "Family.h"
#include "Player.h"

const int WAIT_ANIM_TIME = 5;
const int MAX_HP = 3;
const int JUMP_POWER = -13;
const int RANGE = 150;
const int MOVE_SPEED = -2;

EnemyHugDaemon::EnemyHugDaemon( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP ) {
	setRadius( 36 );
}


EnemyHugDaemon::~EnemyHugDaemon( ) {
}

void EnemyHugDaemon::act( ) {
	Vector vec = getVec( );
	vec.x = MOVE_SPEED;
	for ( int i = 0; i < ACE_PLAYER_NUM; i++ ) {
		 PlayerPtr player = Family::getTask( )->getPlayer( i );
		 Vector diff = player->getPos( ) - getPos( );
		 if ( diff.getLength( ) < RANGE &&
			  player->getPos( ).x < getPos( ).x &&
			  player->getPos( ).y < getPos( ).y &&
			  isStanding( ) ) {
				vec.y = JUMP_POWER;
		 }
	}
	setVec( vec );
}

Chip EnemyHugDaemon::getChip( ) const {
	const int ANIM[ ] = {
		13, 14, 15, 14
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	Chip chip = Chip( );
	chip.tx = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] * 64;
	chip.ty = 9 * 64;
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