#include "ViewerStreet.h"
#include "Drawer.h"
#include "Family.h"
#include "Map.h"

ViewerStreet::ViewerStreet( ) {
	MapPtr map = Map::getTask( );
	_num = map->getPageNum( );

	DrawerPtr drawer( Drawer::getTask( ) );
	char buf[ 256 ];

	for ( int i = 0; i < _num; i++ ) {
		sprintf_s( buf, "Map/back_%003d.png", i );
		_images.push_back( drawer->createImage( buf ) );
	}

	for ( int i = 0; i < _num; i++ ) {
		sprintf_s( buf, "Map/front_%003d.png", i );
		_images.push_back( drawer->createImage( buf ) );
	}

}

ViewerStreet::~ViewerStreet( ) {
}

void ViewerStreet::draw( LAYER layer ) const {
	FamilyConstPtr family( Family::getTask( ) );
	double camera_pos = family->getCameraPos( );
	int origin = ( int )camera_pos / GRAPH_SIZE;
	int offset = 0;
	if ( layer == LAYER_FRONT ) {
		offset = _num;
	}
	for ( int i = 0; i < ACE_MAP_SIZE; i++ ) {
		int sx1 = GRAPH_SIZE * i - ( (int)camera_pos % GRAPH_SIZE );
		int idx = ( origin + i) % _num + offset;
		_images[ idx ]->setPos( sx1, VIEW_STREET_Y );
		_images[ idx ]->draw( );
	}
}
