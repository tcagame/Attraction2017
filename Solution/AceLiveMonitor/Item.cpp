#include "Item.h"
static const int MAX_HP = 0;

Item::Item( const Vector& pos ) :
Character( pos, SMALL_CHAR_GRAPH_SIZE, MAX_HP ) {
}

Item::~Item( ) {
}
