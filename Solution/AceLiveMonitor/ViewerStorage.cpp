#include "ViewerStorage.h"
#include "Drawer.h"
#include "Family.h"
#include "Storage.h"
#include "Item.h"

ViewerStorage::ViewerStorage( ) {
	_image = Drawer::getTask( )->createImage( "Item/item.png" );
}


ViewerStorage::~ViewerStorage( ) {
}

void ViewerStorage::draw( ) const {
	FamilyConstPtr family( Family::getTask( ) );
	int camera_pos = ( int )family->getCameraPos( );

	StoragePtr storage( Storage::getTask( ) );
	std::list< ItemPtr > items = storage->getItems( );
	std::list< ItemPtr >::iterator ite = items.begin( );
	while ( ite != items.end( ) ) {
		ItemPtr item = *ite;
		if ( !item ) {
			ite++;
			continue;
		}
		int add_sx = -camera_pos;
		int add_sy = VIEW_STREET_Y;
		if ( item->getArea( ) == AREA_EVENT ) {
			add_sx = 0;
			add_sy = VIEW_EVENT_Y;
		}
		Chip chip = item->getChip( );
		chip.sx1 += add_sx;
		chip.sx2 += add_sx;
		chip.sy1 += add_sy;
		chip.sy2 += add_sy;
		_image->setRect( chip.tx, chip.ty, chip.size, chip.size );
		_image->setPos( chip.sx1, chip.sy1, chip.sx2, chip.sy2 );
		_image->draw( );
		ite++;
	}
}