#include "ItemEnhancedCharge.h"
#include "SynchronousData.h"

const int PRICE = 50000;

ItemEnhancedCharge::ItemEnhancedCharge( const Vector& pos ) :
ShopItem( pos, PRICE ) {
}


ItemEnhancedCharge::~ItemEnhancedCharge( ) {
}

void ItemEnhancedCharge::act( ) {
}

void ItemEnhancedCharge::setSynchronousData( int camera_pos ) const {
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
	data->addObject( area, SynchronousData::TYPE_ITEM, 9, attribute, x, y, 32 );
}
