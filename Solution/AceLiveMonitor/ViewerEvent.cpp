#include "ViewerEvent.h"
#include "Drawer.h"
#include "ace_define.h"

ViewerEvent::ViewerEvent( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_title = drawer->createImage( "Event/title_logo.png" );
	_frame = drawer->createImage( "Event/event_frame.png");
}

ViewerEvent::~ViewerEvent( ) {
}

void ViewerEvent::draw( ) const {
	_title->setPos( 0, VIEW_TITLE_Y );
	_title->draw( );
	_frame->setPos( 0, VIEW_TITLE_Y );
	_frame->draw( );
}