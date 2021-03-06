#include "ViewerEvent.h"
#include "Drawer.h"
#include "ace_define.h"

ViewerEvent::ViewerEvent( ) {
	DrawerPtr drawer( Drawer::getTask( ) );

	char buf[ 256 ];
	for ( int i = 0; i < EVENT_PAGE_NUM; i++ ) {
		//RED_DAEMON
		sprintf_s( buf, "Event/reddaemon/back_%003d.png", i );
		_images[ EVENT_REDDAEMON * EVENT_PAGE_NUM + i ] = drawer->createImage( buf );

		//FIRE
		sprintf_s( buf, "Event/fire/back_%003d.png", i );
		_images[ EVENT_FLAME * EVENT_PAGE_NUM + i ] = drawer->createImage( buf );
		//TREE
		sprintf_s( buf, "Event/tree/back_%003d.png", i );
		_images[ EVENT_WOOD * EVENT_PAGE_NUM + i ] = drawer->createImage( buf );
		//ROCK
		sprintf_s( buf, "Event/rock/back_%003d.png", i );
		_images[ EVENT_MINERAL * EVENT_PAGE_NUM + i ] = drawer->createImage( buf );
		//SHOP
		sprintf_s( buf, "Event/shop/back_%003d.png", i );
		_images[ EVENT_SHOP * EVENT_PAGE_NUM + i ] = drawer->createImage( buf );
		//RYUGU
		sprintf_s( buf, "Event/ryugu/back_%003d.png", i );
		_images[ EVENT_RYUGU * EVENT_PAGE_NUM + i ] = drawer->createImage( buf );
		//LAKE
		sprintf_s( buf, "Event/lake/back_%003d.png", i );
		_images[ EVENT_LAKE * EVENT_PAGE_NUM + i ] = drawer->createImage( buf );
		//CALL
		sprintf_s( buf, "Event/call/back_%003d.png", i );
		_images[ EVENT_CALL * EVENT_PAGE_NUM + i ] = drawer->createImage( buf );
		//GAMBLE
		sprintf_s( buf, "Event/gamble/back_%003d.png", i );
		_images[ EVENT_GAMBLE * EVENT_PAGE_NUM + i ] = drawer->createImage( buf );
		//ENMA
		sprintf_s( buf, "Event/enma/back_%003d.png", i );
		_images[ EVENT_ENMA * EVENT_PAGE_NUM + i ] = drawer->createImage( buf );
		//BUDHA
		sprintf_s( buf, "Event/shaka/back_%003d.png", i );
		_images[ EVENT_BUDHA * EVENT_PAGE_NUM + i ] = drawer->createImage( buf );
	}

	_image_escape = drawer->createImage( "Event/event_escape.png" );
}

ViewerEvent::~ViewerEvent( ) {
}

void ViewerEvent::draw( EVENT event, int sx, int sy ) const {
	for ( int i = 0; i < EVENT_PAGE_NUM; i++ ) {
		_images[ event * EVENT_PAGE_NUM + i ]->setPos( i * VIEW_WIDTH + sx, sy );
		_images[ event * EVENT_PAGE_NUM + i ]->draw( );
	}

	static int count = 0;
	count++;
	_image_escape->setBlend( Image::BLEND_ALPHA, abs( cos( PI * count / 60 ) ) );

	switch ( event ) {
	case EVENT_REDDAEMON:
	case EVENT_FLAME    :
	case EVENT_WOOD     :
	case EVENT_MINERAL  :
		_image_escape->setRect( 0, 0, 128, 64 );
		_image_escape->setPos( 256 - 64, 0 );
		_image_escape->draw( );
		break;
	case EVENT_GAMBLE   :
	case EVENT_SHOP     :
	case EVENT_RYUGU    :
		_image_escape->setRect( 0, 64, 128, 64 );
		_image_escape->setPos( 256 - 64, 0 );
		_image_escape->draw( );
		break;
	case EVENT_LAKE     :
	case EVENT_CALL     :
	case EVENT_ENMA     :
	case EVENT_BUDHA    : 
		break;
	}
}