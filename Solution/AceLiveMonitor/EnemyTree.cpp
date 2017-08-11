#include "EnemyTree.h"
#include "Military.h"
#include "EnemyTreeNuts.h"

const int WAIT_ANIM_TIME = 5;
const int CHIP_SIZE = 192;
const int ATTACK_TIME = 30;
const int MAX_GENERATE_NUM = 9;
const Vector GENERATE_POS[ MAX_GENERATE_NUM ] = {
	Vector( 6, 850 - 736 ),
	Vector( 12, 875 - 736 ),
	Vector( 45, 876 - 736 ),
	Vector( 84, 822 - 736 ),
	Vector( 126, 796 - 736 ),
	Vector( 176, 810 - 736 ),
	Vector( 175, 849 - 736 ),
	Vector( 159, 864 - 736 ),
	Vector( 142, 874 - 736 )
};

EnemyTree::EnemyTree( const Vector& pos ) :
Enemy( pos, CHIP_SIZE ) {
	setRadius( 36 );
}


EnemyTree::~EnemyTree( ) {
}

void EnemyTree::act( ) {
	if ( !( getActCount( ) % ATTACK_TIME ) ) {
		MilitaryPtr military( Military::getTask( ) );
		Vector origin = getPos( ) - Vector( CHIP_SIZE / 2, CHIP_SIZE );
		military->popUp( EnemyPtr( new EnemyTreeNuts( origin + GENERATE_POS[ rand( ) % 9 ] ) ) );
	}
}

Chip EnemyTree::getChip( ) const {
	const int ANIM[ ] = {
		0, 1
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	Chip chip = Chip( );
	chip.tx = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] * CHIP_SIZE;
	chip.ty = 7 * 128;
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