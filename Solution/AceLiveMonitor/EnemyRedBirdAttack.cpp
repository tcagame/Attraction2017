#include "EnemyRedBirdAttack.h"

static const int WAIT_ANIM_TIME = 5;
static const int MAX_HP = 2;

EnemyRedBirdAttack::EnemyRedBirdAttack( const Vector& pos ) :
Enemy( pos, SMALL_CHAR_GRAPH_SIZE, MAX_HP ) {
	setRadius( 18 );
}


EnemyRedBirdAttack::~EnemyRedBirdAttack( ) {
}

void EnemyRedBirdAttack::act( ) {
	if ( isStanding( ) ) damage( -1 );
}

Chip EnemyRedBirdAttack::getChip( ) const {
	const int ANIM[ ] = {
		0, 1, 2, 1
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	Chip chip = Chip( );
	chip.tx = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] * 32;
	chip.ty = 0 * 32;
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