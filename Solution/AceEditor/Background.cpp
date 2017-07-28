#include "Background.h"
#include "Drawer.h"


Background::Background( ) {
}


Background::~Background( ) {
}


bool Background::loadImage( std::string directory, std::string filename ) {
	ImagePtr image = Drawer::getTask( )->createImage( ( directory + filename ).c_str( ) );
	if ( image == ImagePtr( ) ) {
		return false;
	}
	_bg[ filename ] = image;
	return true;
}

ImagePtr Background::getImage( std::string filename ) {
	if( _bg.find( filename ) == _bg.end( ) ) {
		return ImagePtr( );
	}
	return _bg[ filename ];
}