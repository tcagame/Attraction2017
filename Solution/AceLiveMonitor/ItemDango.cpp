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

void ItemDango::setSynchronousData( unsigned char type, int camera_pos ) const {
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
	data->addObject( area, type, 6, attribute, x, y, 64 );
}