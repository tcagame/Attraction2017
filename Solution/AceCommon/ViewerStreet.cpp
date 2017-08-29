#include "ViewerStreet.h"
#include "Drawer.h"
#include "ace_define.h"
#include "Binary.h"
#include "Application.h"

ViewerStreet::ViewerStreet( ) {
	// マップページ数読み取り
	{
		BinaryPtr binary(new Binary);
		ApplicationPtr app(Application::getInstance());
		app->loadBinary(STREET_MAPDATA_FILENAME, binary);
		binary->read((void*)&_num, sizeof(int));
	}

	DrawerPtr drawer( Drawer::getTask( ) );
	char buf[ 256 ];

	_images.resize( _num * 2 );
	for ( int i = 0; i < _num; i++ ) {
		sprintf_s( buf, "Street/back_%003d.png", i );
		_images[ _num * 0 + i ] = drawer->createImage( buf );
		sprintf_s( buf, "Street/front_%003d.png", i );
		_images[ _num * 1 + i ] = drawer->createImage( buf );
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
