#include "ItemTree.h"

ItemTree::ItemTree( const Vector& pos ) :
Item( pos ) {
}


ItemTree::~ItemTree( ) {
}

Chip ItemTree::getChip( ) const {
	Chip chip = Chip( );
	Vector pos = getPos( );
	chip.size = getChipSize( );
	chip.tx = 128;
	chip.ty = 128;
	chip.sx1 = ( int )pos.x - chip.size / 2;
	chip.sy1 = ( int )pos.y - chip.size;
	chip.sx2 = chip.sx1 + chip.size;
	chip.sy2 = chip.sy1 + chip.size;
	return chip;
}

void ItemTree::act( ) {

}