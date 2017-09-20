#include "PopMoney.h"
#include "Storage.h"

const int MAX_POP_COUNT = 1000;

PopMoney::PopMoney( const Vector& pos, unsigned char type ) :
Pop( pos ),
_type( type ),
_count( MAX_POP_COUNT ) {
}


PopMoney::~PopMoney( ) {
}

void PopMoney::update( ) {
	if ( !_item.expired( ) ) {
		return;
	}
	if ( _count > MAX_POP_COUNT ) {
		if ( isInScreen( ) ) {
			ItemPtr item = ItemPtr( new ItemMoney( getPos( ), _type, AREA_STREET ) );
			Storage::getTask( )->add( item );
			_item = item;
			_count = 0;
		}
	}
	_count++;
}
