#include "ItemToku.h"



ItemToku::ItemToku( Vector pos ) :
Item( pos ) {
}


ItemToku::~ItemToku( ) {
}

void ItemToku::act( ) {
}

Chip ItemToku::getChip( ) const {
	Chip chip = Chip( );
	Vector pos = getPos( );
	chip.size = getChipSize( );
	chip.sx1 = ( int )pos.x - chip.size / 2;
	chip.sy1 = ( int )pos.y - chip.size;
	chip.sx2 = chip.sx1 + chip.size;
	chip.sy2 = chip.sy1 + chip.size;
	chip.tx = 64;
	chip.ty = 128;
	return chip;
}