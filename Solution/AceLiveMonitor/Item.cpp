#include "Item.h"
static const int POWER = 0;

Item::Item( const Vector& pos ) :
Character( pos, SMALL_CHAR_GRAPH_SIZE, POWER ) {
}

Item::~Item( ) {
}
