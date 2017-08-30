#include "RockItem.h"

RockItem::RockItem( const Vector& pos, DOLL doll ) :
RockCharacter( pos, doll, 10, 10 ),
_repop( true ) {
}

RockItem::~RockItem( ) {
}

void RockItem::act( ) {
}

void RockItem::setRepop( bool repop ) {
	_repop = repop;
}

bool RockItem::isRepop( ) const {
	return _repop;
}
