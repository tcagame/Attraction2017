#include "Structure.h"
#include "LoadCSV.h"
#include "ace_define.h"
#include "Drawer.h"

Structure::Structure( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	LoadCSV csv( "Resource/Ace/Editor/structure/structure_list", STRUCTURE_LIST_NUM );
	for ( int i = 0; i < csv.getSize( ); i++ ) {
		std::string path = csv.getData( i );
		if ( path == "" ) {
			continue;
		}
		path = "structure/" + path;
		
		_image.push_back( drawer->createImage( path.c_str( ) ) );
	}
}


Structure::~Structure( ) {
}

ImagePtr Structure::getImage( int idx ) const {
	if ( ( int )_image.size( ) <= idx ) {
		return ImagePtr( );
	}
	return _image[ idx ];
}

int Structure::getSize( ) const {
	return ( int )_image.size( );
}

