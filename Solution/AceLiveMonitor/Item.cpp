#include "Item.h"
static const int MAX_HP = 0;

Item::Item( const Vector& pos ) :
Character( pos, ITEM_GRAPH_SIZE, MAX_HP ) {
	setVec( Vector( 0, -6 ) );
}

Item::~Item( ) {
}
