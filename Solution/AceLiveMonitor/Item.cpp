#include "Item.h"


Item::Item( const Vector& pos, int chip_size, bool mass ) :
Character( pos, chip_size, 0, mass ) {
	if ( mass ) {
		setVec( Vector( 0, -6 ) );
	}
}

Item::~Item( ) {
}
