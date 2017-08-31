#include "Ground.h"
#include "LoadCSV.h"
#include "Drawer.h"


Ground::Ground( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	LoadCSV csv( "Resource/Ace/Editor/ground/ground_list", GROUND_LIST_NUM );
	const int num = ( int )csv.getSize( );
	for ( int i = 0; i < num; i++ ) {
		std::string path = csv.getData( i );
		if ( path != "" ) {
			path = "ground/" + path;
			_image[ i ] = drawer->createImage( path.c_str( ) );
		}
	}
}


Ground::~Ground( ) {
}

ImagePtr Ground::getImage( int idx ) const {
	if ( _image.size( ) <= idx ) {
		return ImagePtr( );
	}
	return _image[ idx ];
}

int Ground::getSize( ) const {
	return ( int )_image.size( );
}
