#include "ViewerTitle.h"
#include "Drawer.h"
#include "Image.h"

ViewerTitle::ViewerTitle( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_image = drawer->createImage( "Title/title_logo.png" );
}

ViewerTitle::~ViewerTitle( ) {
}

void ViewerTitle::draw( ) {
	_image->draw( );
}