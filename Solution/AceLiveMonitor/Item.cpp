#include "Item.h"

Item::Item( const Vector& pos, AREA area, int chip_size ) :
Character( pos, chip_size, 0, false ) {
	setArea( area );
}

Item::~Item( ) {
}

void Item::setDrop( ) {
	setMass( true );
	setVec( Vector( 0, -6 ) );

}
