#include "Item.h"


Item::Item( const Vector& pos, int chip_size ) :
Character( pos, chip_size, 0 ) {
	setVec( Vector( 0, -6 ) );
}

Item::~Item( ) {
}
