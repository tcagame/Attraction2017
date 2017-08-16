#include "NPCObaba.h"

static const int TIME = 60;
static const int WAIT_ANIM_TIME = 10;
static const int MAX_HP = 6;

NPCObaba::NPCObaba( const Vector& pos ) :
Character( pos, BIG_CHAR_GRAPH_SIZE, MAX_HP ) {
	setVec( Vector( 1, 0 ) );
}


NPCObaba::~NPCObaba( ) {
}

void NPCObaba::act( ) {
	if ( !( getActCount( ) % TIME ) ) {
		setVec( getVec( ) * -1 );
	}
}

Chip NPCObaba::getChip( ) const {
	Chip chip = Chip( );
	Vector pos = getPos( );
	chip.size = getChipSize( );
	
	const int ANIM_LEFT[ ] = {
		0, 1
	};
	const int ANIM_RIGHT[ ] = {
		2, 3
	};
	if ( getDir( ) == DIR_LEFT ) {
		const int anim_size = sizeof( ANIM_LEFT ) / sizeof( ANIM_LEFT[ 0 ] );
		chip.tx = ANIM_LEFT[ ( getActCount( ) / WAIT_ANIM_TIME ) % anim_size ] * chip.size;
	}
	if ( getDir( ) == DIR_RIGHT ) {
		const int anim_size = sizeof( ANIM_RIGHT ) / sizeof( ANIM_RIGHT[ 0 ] );
		chip.tx = ANIM_RIGHT[ ( getActCount( ) / WAIT_ANIM_TIME ) % anim_size ] * chip.size;
	}
	chip.ty = 256;
	
	chip.sx1 = ( int )pos.x - chip.size / 2 + chip.size;
	chip.sy1 = ( int )pos.y - chip.size;
	chip.sx2 = chip.sx1 - chip.size;
	chip.sy2 = chip.sy1 + chip.size;
	return chip;
}

void NPCObaba::damage( int force ) {
}