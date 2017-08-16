#include "EnemyHandAttack.h"

static const int WAIT_ANIM_TIME = 1;
static const int POWER = 2;

EnemyHandAttack::EnemyHandAttack( const Vector& pos ) :
Enemy( pos, SMALL_CHAR_GRAPH_SIZE, POWER ) {
	setRadius( 18 );
	Vector vec( -20, -8 );
	setVec( vec );
}


EnemyHandAttack::~EnemyHandAttack( ) {
}

void EnemyHandAttack::act( ) {
	if ( isStanding( ) ) damage( -1 );
}

Chip EnemyHandAttack::getChip( ) const {
	const int ANIM[ ] = {
		0, 1, 2, 3, 4, 5, 6, 7
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	Chip chip = Chip( );
	chip.tx = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] * 32;
	chip.ty = 7 * 32;
	chip.size = getChipSize( );
	
	Vector pos = getPos( );
	chip.sx1 = ( int )pos.x - chip.size / 2;
	chip.sy1 = ( int )pos.y - chip.size;
	chip.sx2 = chip.sx1 + chip.size;
	chip.sy2 = chip.sy1 + chip.size;
	
	return chip;
}