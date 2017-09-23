#include "ItemDango.h"
#include "SynchronousData.h"

const int PRICE = 100;

ItemDango::ItemDango( const Vector& pos ) :
ShopItem( pos, PRICE ) {
}


ItemDango::~ItemDango( ) {
}

void ItemDango::act( ) {
}

void ItemDango::setSynchronousData( int camera_pos ) const {
	if ( getPhase( ) == PHASE_FLASH ) {
		if ( getActCount( ) / getFlashWaitTime( ) % 2 == 0 ) {
			return;
		}
	}
	Vector pos = getPos( );
	int x = ( int )pos.x;
	int y = ( int )pos.y;

	AREA area = AREA_EVENT;
	if ( getArea( ) == AREA_STREET ) {
		x -= camera_pos;
		area = AREA_STREET;
	}
	unsigned char attribute = 0;
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->addObject( area, SynchronousData::TYPE_ITEM, 11, attribute, x, y, 32 );
}
