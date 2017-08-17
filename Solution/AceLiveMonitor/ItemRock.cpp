#include "ItemRock.h"

ItemRock::ItemRock( const Vector& pos ) :
Item( pos ) {
}


ItemRock::~ItemRock( ) {
}

Chip ItemRock::getChip( ) const {
	Chip chip = Chip( );
	Vector pos = getPos( );
	chip.size = getChipSize( );
	chip.tx = 192;
	chip.ty = 128;
	chip.sx1 = ( int )pos.x - chip.size / 2;
	chip.sy1 = ( int )pos.y - chip.size;
	chip.sx2 = chip.sx1 + chip.size;
	chip.sy2 = chip.sy1 + chip.size;
	return chip;
}

void ItemRock::act( ) {

}