#include "NPCMiko.h"

const int WAIT_ANIM_TIME = 10;

NPCMiko::NPCMiko( const Vector& pos ) :
Character( pos, BIG_CHAR_GRAPH_SIZE ) {
}


NPCMiko::~NPCMiko( ) {
}

void NPCMiko::act( ) {
}

Chip NPCMiko::getChip( ) const {
	Chip chip = Chip( );
	Vector pos = getPos( );
	chip.size = getChipSize( );
	chip.sx1 = ( int )pos.x - chip.size / 2;
	chip.sy1 = ( int )pos.y - chip.size;
	chip.sx2 = chip.sx1 + chip.size;
	chip.sy2 = chip.sy1 + chip.size;
	
	const int ANIM[ ] = {
		0, 1, 2
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	int cx = ANIM[ ( getActCount( ) / WAIT_ANIM_TIME ) % anim_size ];
	//int cy = 2;
	chip.tx = cx * chip.size;
	chip.ty = 128;
	return chip;
}

void NPCMiko::damage( int force ) {
}