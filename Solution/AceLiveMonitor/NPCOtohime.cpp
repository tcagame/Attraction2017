#include "NPCOtohime.h"

const int WAIT_ANIM_TIME = 10;

NPCOtohime::NPCOtohime( const Vector& pos ):
Character( pos, BIG_CHAR_GRAPH_SIZE, false ) {
}


NPCOtohime::~NPCOtohime( ) {
}

void NPCOtohime::act( ) {
}

Chip NPCOtohime::getChip( ) const {
	Chip chip = Chip( );
	Vector pos = getPos( );
	chip.size = getChipSize( );
	chip.sx1 = ( int )pos.x - chip.size / 2;
	chip.sy1 = ( int )pos.y - chip.size;
	chip.sx2 = chip.sx1 + chip.size;
	chip.sy2 = chip.sy1 + chip.size;
	
	const int ANIM[ ] = {
		0, 1, 2, 3
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	int cx = ANIM[ ( getActCount( ) / WAIT_ANIM_TIME ) % anim_size ];
	//int cy = 2;
	chip.tx = cx * chip.size;
	chip.ty = 512;
	return chip;
}

void NPCOtohime::damage( int force ) {
}