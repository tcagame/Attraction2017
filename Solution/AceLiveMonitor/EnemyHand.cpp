#include "EnemyHand.h"
#include "Military.h"
#include "EnemyHandAttack.h"

static const int WAIT_ANIM_TIME = 3;
static const int ATTACK_TIME = WAIT_ANIM_TIME * 21;
static const int MAX_HP = 3;

EnemyHand::EnemyHand( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP ) {
	setRadius( 36 );
}


EnemyHand::~EnemyHand( ) {
}

void EnemyHand::act( ) {
	const Vector genelate_pos( 35, 40 );
	if ( !( ( getActCount( ) + WAIT_ANIM_TIME * 12 ) % ATTACK_TIME ) ) {
		MilitaryPtr military( Military::getTask( ) );
		Vector origin = getPos( ) - Vector( NORMAL_CHAR_GRAPH_SIZE / 2, NORMAL_CHAR_GRAPH_SIZE );
		military->popUp( EnemyPtr( new EnemyHandAttack( origin  + genelate_pos ) ) );
	}
}

Chip EnemyHand::getChip( ) const {
	const int ANIM[ ] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 2, 1, 0
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	Chip chip = Chip( );
	chip.tx = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] * 64;
	chip.ty = 2 * 64;
	chip.size = getChipSize( );
	
	Vector pos = getPos( );
	chip.sx1 = ( int )pos.x - chip.size / 2 + chip.size;
	chip.sy1 = ( int )pos.y - chip.size;
	chip.sx2 = chip.sx1 - chip.size;
	chip.sy2 = chip.sy1 + chip.size;
	
	return chip;
}
