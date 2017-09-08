#include "RockPopItem.h"
#include "RockStorage.h"
#include "RockItemBubble.h"

static const int MAX_POP_COUNT = 100;

RockPopItem::RockPopItem( RockItemPtr item, bool bubble ) :
_item( item ),
_bubble( bubble ),
_count( 0 ){
}


RockPopItem::~RockPopItem( ) {
}

void RockPopItem::update( ) {
	_count++;
	if ( _count > MAX_POP_COUNT ) {
		if ( _bubble ) {			
			RockStorage::getTask( )->addBubble( std::dynamic_pointer_cast< RockItemBubble >( _item ) );
		} else {
			RockStorage::getTask( )->addItem( _item );
		}
	}
}

bool RockPopItem::isFinished( ) const {
	return ( _count > MAX_POP_COUNT );
}