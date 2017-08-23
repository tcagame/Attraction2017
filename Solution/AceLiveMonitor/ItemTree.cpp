#include "ItemTree.h"
#include "SynchronousData.h"

ItemTree::ItemTree( const Vector& pos ) :
Item( pos ) {
}


ItemTree::~ItemTree( ) {
}

void ItemTree::act( ) {
}

void ItemTree::setSynchronousData( unsigned char type, int camera_pos ) const {
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
	data->addObject( area, type, 36, attribute, x, y );
}
