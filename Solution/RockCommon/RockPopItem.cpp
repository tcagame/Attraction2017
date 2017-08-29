#include "RockPopItem.h"
#include "RockStorage.h"

static const int MAX_POP_COUNT = 100;

RockPopItem::RockPopItem( RockItemPtr item ) :
_item( item ),
_count( 0 ){
}


RockPopItem::~RockPopItem( ) {
}

void RockPopItem::update( ) {
	_count++;
	if ( _count > MAX_POP_COUNT ) {
		RockStorage::getTask( )->addItem( _item );
	}
}

bool RockPopItem::isFinished( ) const {
	return ( _count > MAX_POP_COUNT );
}