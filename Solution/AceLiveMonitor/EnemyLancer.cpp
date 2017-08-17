#include "EnemyLancer.h"
#include "Family.h"
#include "Player.h"

const int WAIT_ANIM_TIME = 2;
const int MAX_HP = 3;
const int MOVE_SPEED = -3;
const int RANGE = 150;

EnemyLancer::EnemyLancer( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP ) {
	setRadius( 36 );
	setVec( Vector( MOVE_SPEED, 0 ) );
}

EnemyLancer::~EnemyLancer( ) {
}

void EnemyLancer::act( ) {
	Vector vec = getVec( );
	for ( int i = 0; i < ACE_PLAYER_NUM; i++ ) {
		 PlayerPtr player = Family::getTask( )->getPlayer( i );
		 Vector diff = player->getPos( ) - getPos( );
		 if ( diff.getLength( ) < RANGE &&
			  player->getPos( ).x < getPos( ).x ) {
				vec.x = MOVE_SPEED * 3;
		 }
	}
	setVec( vec );
}

Chip EnemyLancer::getChip( ) const {
	const int ANIM[ ] = {
		0, 1, 2, 3, 4
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
