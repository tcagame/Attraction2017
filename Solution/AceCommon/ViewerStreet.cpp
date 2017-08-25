#include "ViewerStreet.h"
#include "Drawer.h"
#include "MapStreet.h"
#include "ace_define.h"

ViewerStreet::ViewerStreet( ) {
	MapStreetPtr map = MapStreet::getTask( );
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

void ViewerStreet::draw( LAYER layer, int sx, int sy, int camera_pos ) const {
	int origin = camera_pos / GRAPH_SIZE;
	int offset = 0;
	if ( layer == LAYER_FRONT ) {
		offset = _num;
	}
	int y = sy;
	for ( int i = 0; i < ACE_MAP_SIZE; i++ ) {
		int x = GRAPH_SIZE * i - ( camera_pos % GRAPH_SIZE ) + sx;
		int idx = ( origin + i ) % _num + offset;
		_images[ idx ]->setPos( x, y );
		_images[ idx ]->draw( );
	}
}
