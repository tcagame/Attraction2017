#include "ItemEnhancedCharge.h"
#include "SynchronousData.h"

const int PRICE = 100;

ItemEnhancedCharge::ItemEnhancedCharge( const Vector& pos ) :
ShopItem( pos, PRICE ) {
}


ItemEnhancedCharge::~ItemEnhancedCharge( ) {
}

void ItemEnhancedCharge::act( ) {
}

void ItemEnhancedCharge::setSynchronousData( unsigned char type, int camera_pos ) const {
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
	data->addObject( area, type, 4, attribute, x, y, 64 );
}
