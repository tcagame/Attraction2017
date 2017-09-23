#include "ItemBox.h"
#include "SynchronousData.h"

const Vector INIT_POS( 1280 / 2, 256 - 16 );

ItemBox::ItemBox( ) :
Item( INIT_POS, AREA_EVENT ) {
}

ItemBox::~ItemBox( ) {
}

void ItemBox::act( ) {
}

void ItemBox::setSynchronousData( int camera_pos ) const {
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
	data->addObject( area, SynchronousData::TYPE_ITEM, 12, attribute, x, y, 32 );
}
