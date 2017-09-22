#include "ItemYokaiSoup.h"
#include "SynchronousData.h"

const int PRICE = 500;


ItemYokaiSoup::ItemYokaiSoup( const Vector& pos ) :
ShopItem( pos, PRICE ) {
}


ItemYokaiSoup::~ItemYokaiSoup( ) {
}

void ItemYokaiSoup::act( ) {
}

void ItemYokaiSoup::setSynchronousData( int camera_pos ) const {
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
	data->addObject( area, SynchronousData::TYPE_ITEM, 10, attribute, x, y, 32 );
}