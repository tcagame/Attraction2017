#include "Ground.h"
#include "LoadCSV.h"
#include "ace_define.h"
#include "Drawer.h"


Ground::Ground( ) {
	DrawerPtr drawer = Drawer::getTask( );
	LoadCSV csv( "../Resource/Ace/Editor/ground/ground_list", GROUND_LIST_NUM );
	for ( int i = 0; i < csv.getSize( ); i++ ) {
		std::string path = csv.getData( i );
		if ( path == "" ) {
			continue;
		}
		path = "ground/" + path;
		
		_image.push_back( drawer->createImage( path.c_str( ) ) );
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
