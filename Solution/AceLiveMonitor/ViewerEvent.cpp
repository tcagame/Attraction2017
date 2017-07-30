#include "ViewerEvent.h"
#include "Drawer.h"
#include "ace_define.h"


ViewerEvent::ViewerEvent(  ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_frame = drawer->createImage( "Event/event_frame.png");

	char buf[ 256 ];
	//TITLE
	_images.push_back( drawer->createImage( "Event/title_logo.png" ) );
	//RED_DEMON
	for ( int i = 0; i < EVENT_PAGE_NUM; i++ ) {
		sprintf_s( buf, "Event/event_akaoni_%d.png", i + 1 );
		_images.push_back( drawer->createImage( buf ) );
	}
	_type = TYPE_RED_DEMON;
}

ViewerEvent::~ViewerEvent( ) {
}

void ViewerEvent::draw( ) const {
	if( _type == TYPE_TITLE ) {
		_images[ 0 ]->setPos( 0, VIEW_TITLE_Y );
		_images[ 0 ]->draw( );
	} else {
		int sx = 256;
		for ( int i = 0; i < 8; i++ ) {
			int idx = _type + ( i % EVENT_PAGE_NUM );
			_images[ idx ]->setPos( i * sx, VIEW_TITLE_Y );
			_images[ idx ]->draw( );
		}
	}
	_frame->setPos( 0, VIEW_TITLE_Y );
	_frame->draw( );
}