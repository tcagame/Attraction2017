#include "Item.h"
static const int MAX_HP = 0;

Item::Item( const Vector& pos, int chip_size ) :
Character( pos, chip_size, MAX_HP ) {
	setVec( Vector( 0, -6 ) );
}

Item::~Item( ) {
}
