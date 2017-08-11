#include "ItemFire.h"

ItemFire::ItemFire( const Vector& pos ) :
Item( pos ) {
}


ItemFire::~ItemFire( ) {
}

Chip ItemFire::getChip( ) const {
	Chip chip = Chip( );
	Vector pos = getPos( );
	chip.size = getChipSize( );
	chip.tx = 160;
	chip.ty = 128;
	chip.sx1 = ( int )pos.x - chip.size / 2;
	chip.sy1 = ( int )pos.y - chip.size;
	chip.sx2 = chip.sx1 + chip.size;
	chip.sy2 = chip.sy1 + chip.size;
	return chip;
}

void ItemFire::act( ) {

}