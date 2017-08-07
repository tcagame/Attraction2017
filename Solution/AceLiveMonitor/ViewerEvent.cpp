#include "ViewerEvent.h"
#include "Drawer.h"
#include "ace_define.h"
#include "Family.h"
#include "MapEvent.h"


ViewerEvent::ViewerEvent(  ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_frame = drawer->createImage( "Event/event_frame.png");

	char buf[ 256 ];
	//TITLE
	_images.push_back( drawer->createImage( "Event/title_logo.png" ) );
	//RED_DEMON
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
	//TREE
	for ( int i = 0; i < EVENT_PAGE_NUM; i++ ) {
		sprintf_s( buf, "Event/rock/back_%003d.png", i );
		_images.push_back( drawer->createImage( buf ) );
	}
}

ViewerEvent::~ViewerEvent( ) {
}

void ViewerEvent::draw( ) const {
	MapEventPtr map( MapEvent::getTask( ) );
	TYPE type = map->getType( );
	if( type == TYPE_TITLE ) {
		_images[ 0 ]->setPos( 0, VIEW_TITLE_Y );
		_images[ 0 ]->draw( );
	} else {
		int idx = 0;
		int sx = 256;
		for ( int i = 0; i < 8; i++ ) {
			switch ( type ) {
			case TYPE_RED_DEMON:
				idx = type + ( i % EVENT_PAGE_NUM );
				break;
			case TYPE_FIRE:
				if ( i / EVENT_PAGE_NUM > 0 ) {
					idx = type + 3; 
				} else {
					idx = type + i;
				}
				case TYPE_TREE:
				if ( i / EVENT_PAGE_NUM > 0 ) {
					idx = type + 3; 
				} else {
					idx = type + i;
				}
				break;
				case TYPE_ROCK:
				if ( i / EVENT_PAGE_NUM > 0 ) {
					idx = type + 3; 
				} else {
					idx = type + i;
				}
				break;
			}
			_images[ idx ]->setPos( i * sx, VIEW_TITLE_Y );
			_images[ idx ]->draw( );
		}
	}
	_frame->setPos( 0, VIEW_TITLE_Y );
	_frame->draw( );
}