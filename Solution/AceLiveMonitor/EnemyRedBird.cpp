#include "EnemyRedBird.h"
#include "EnemyRedBirdAttack.h"
#include "Military.h"

const int WAIT_ANIM_TIME = 5;
const int ATTACK_TIME = 30;
const int MAX_HP = 3;
const int MOVE_SPEED = -5;

EnemyRedBird::EnemyRedBird( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP, false ) {
	setRadius( 36 );
}


EnemyRedBird::~EnemyRedBird( ) {
}

void EnemyRedBird::act( ) {
	setVec( Vector( MOVE_SPEED, 0 ) );
	if ( !( getActCount( ) % ATTACK_TIME ) ) {
		MilitaryPtr military( Military::getTask( ) );
		military->popUp( EnemyPtr( new EnemyRedBirdAttack( getPos( ) ) ) );
	}
}

Chip EnemyRedBird::getChip( ) const {
	const int ANIM[ ] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	Chip chip = Chip( );
	chip.tx = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] * 64;
	chip.ty = 14 * 64;
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