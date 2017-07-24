#include "ViewerStreet.h"
#include "Drawer.h"


ViewerStreet::ViewerStreet( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	for ( int i = 0; i < ACE_MAP_NUM; i++ ) {
		char buf[ 256 ];
		sprintf_s( buf, "back_%003d", i );
		std::string numstr = buf;
		std::string path = "MapData/Img/" + numstr + ".png";
		_image_back[ i ] = drawer->createImage( path.c_str( ) );
	}
	for ( int i = 0; i < ACE_MAP_NUM; i++ ) {
		char buf[ 256 ];
		sprintf_s( buf, "front_%003d", i );
		std::string numstr = buf;
		std::string path = "MapData/Img/" + numstr + ".png";
		_image_front[ i ] = drawer->createImage( path.c_str( ) );
	}
}


ViewerStreet::~ViewerStreet( ) {
}

void ViewerStreet::draw( ) const {
	//back
	for ( int i = 0; i < ACE_MAP_SIZE; i++ ) {
		int sx1 = GRAPH_SIZE * i;
		_image_back[ i % ACE_MAP_NUM ]->setPos( sx1, SCREEN_HEIGHT - GRAPH_SIZE );
		_image_back[ i % ACE_MAP_NUM ]->draw( );
	}
	//front
	for ( int i = 0; i < ACE_MAP_SIZE; i++ ) {
		int sx1 = GRAPH_SIZE * i;
		_image_front[ i % ACE_MAP_NUM ]->setPos( sx1, SCREEN_HEIGHT - GRAPH_SIZE );
		_image_front[ i % ACE_MAP_NUM ]->draw( );
	}
}