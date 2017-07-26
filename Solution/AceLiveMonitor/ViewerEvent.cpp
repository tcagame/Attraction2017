#include "ViewerEvent.h"
#include "Drawer.h"

ViewerEvent::ViewerEvent( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_title = drawer->createImage( "Event/title_logo.png" );
}

ViewerEvent::~ViewerEvent( ) {
}

void ViewerEvent::draw( ) const {
	_title->setPos( 0, 0 );
	_title->draw( );
}