#include "ViewerEvent.h"
#include "Drawer.h"
#include "ace_define.h"
#include "MapEvent.h"

ViewerEvent::ViewerEvent( ) {
	DrawerPtr drawer( Drawer::getTask( ) );

	char buf[ 256 ];
	//TITLE
	_images.push_back( drawer->createImage( "Event/title_logo.png" ) );
	//RED_DAEMON
	for ( int i = 0; i < EVENT_PAGE_NUM; i++ ) {
		sprintf_s( buf, "Event/akaoni/back_%003d.png", i );
		_images.push_back( drawer->createImage( buf ) );
	}
	//FIRE
	for ( int i = 0; i < EVENT_PAGE_NUM; i++ ) {
		sprintf_s( buf, "Event/fire/back_%003d.png", i );
		_images.push_back( drawer->createImage( buf ) );
	}
	//TREE
	for ( int i = 0; i < EVENT_PAGE_NUM; i++ ) {
		sprintf_s( buf, "Event/tree/back_%003d.png", i );
		_images.push_back( drawer->createImage( buf ) );
	}
	//ROCK
	for ( int i = 0; i < EVENT_PAGE_NUM; i++ ) {
		sprintf_s( buf, "Event/rock/back_%003d.png", i );
		_images.push_back( drawer->createImage( buf ) );
	}
	//SHOP
	for ( int i = 0; i < EVENT_PAGE_NUM; i++ ) {
		sprintf_s( buf, "Event/shop/back_%003d.png", i );
		_images.push_back( drawer->createImage( buf ) );
	}
	//RYUGU
	for ( int i = 0; i < EVENT_PAGE_NUM; i++ ) {
		sprintf_s( buf, "Event/ryugu/back_%003d.png", i );
		_images.push_back( drawer->createImage( buf ) );
	}
	//LAKE
	for ( int i = 0; i < EVENT_PAGE_NUM; i++ ) {
		sprintf_s( buf, "Event/lake/back_%003d.png", i );
		_images.push_back( drawer->createImage( buf ) );
	}

}

ViewerEvent::~ViewerEvent( ) {
}

void ViewerEvent::draw( int sx, int sy ) const {
	MapEventPtr map( MapEvent::getTask( ) );
	MapEvent::TYPE type = map->getType( );
	if ( type == MapEvent::TYPE_TITLE ) {
		_images[ 0 ]->setPos( sx, sy );
		_images[ 0 ]->draw( );
	} else {
		int idx = 0;
		int width = 256;
		for ( int i = 0; i < 8; i++ ) {
			switch ( type ) {
			case MapEvent::TYPE_RED_DAEMON:
				idx = type + ( i % EVENT_PAGE_NUM );
				break;
			case MapEvent::TYPE_FIRE:
				if ( i / EVENT_PAGE_NUM > 0 ) {
					idx = type + 3; 
				} else {
					idx = type + i;
				}
			case MapEvent::TYPE_TREE:
				if ( i / EVENT_PAGE_NUM > 0 ) {
					idx = type + 3; 
				} else {
					idx = type + i;
				}
				break;
			case MapEvent::TYPE_ROCK:
				if ( i / EVENT_PAGE_NUM > 0 ) {
					idx = type + 3; 
				} else {
					idx = type + i;
				}
				break;
			case MapEvent::TYPE_SHOP:
				if ( i / EVENT_PAGE_NUM > 0 ) {
					idx = type + 3; 
				} else {
					idx = type + i;
				}
				break;
			case MapEvent::TYPE_RYUGU:
				if ( i / EVENT_PAGE_NUM > 0 ) {
					idx = type + 3; 
				} else {
					idx = type + i;
				}
				break;
			case MapEvent::TYPE_LAKE:
				if ( i / EVENT_PAGE_NUM > 0 ) {
					idx = type + 3; 
				} else {
					idx = type + i;
				}
				break;
			}
			_images[ idx ]->setPos( i * width + sx, sy );
			_images[ idx ]->draw( );
		}
	}
}