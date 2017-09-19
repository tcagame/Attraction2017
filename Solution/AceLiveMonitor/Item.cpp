#include "Item.h"

Item::Item( const Vector& pos, AREA area, int chip_size, bool mass ) :
Character( pos, chip_size, 0, mass ) {
	setArea( area );
	if ( mass ) {
		setVec( Vector( 0, -6 ) );
	}
}

Item::~Item( ) {
}
