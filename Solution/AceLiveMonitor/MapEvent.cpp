#include "MapEvent.h"
#include "Application.h"
#include "Binary.h"
#include "SynchronousData.h"
#include <assert.h>

MapEventPtr MapEvent::getTask( ) {
	return std::dynamic_pointer_cast< MapEvent >( Application::getInstance( )->getTask( getTag( ) ) );
}


MapEvent::MapEvent( ) {
	_event = EVENT_NONE;
	_objects = { };
	load( );
}


MapEvent::~MapEvent( ) {
}


void MapEvent::load( ) {
	std::string filename[ MAX_EVENT ];
	filename[ EVENT_REDDAEMON ] = "Resource/Ace/Event/akaoni/mapdata"; //red deamon
	filename[ EVENT_FIRE      ] = "Resource/Ace/Event/fire/mapdata";  //fire
	filename[ EVENT_TREE      ] = "Resource/Ace/Event/tree/mapdata";	//tree
	filename[ EVENT_ROCK      ] = "Resource/Ace/Event/rock/mapdata";	//rock
	filename[ EVENT_SHOP      ] = "Resource/Ace/Event/shop/mapdata";  //shop
	filename[ EVENT_RYUGU     ] = "Resource/Ace/Event/ryugu/mapdata"; //ryugu
	filename[ EVENT_LAKE      ] = "Resource/Ace/Event/lake/mapdata";  //lake
	filename[ EVENT_GAMBLE    ] = "Resource/Ace/Event/gamble/mapdata";  //gamble

	ApplicationPtr app( Application::getInstance( ) );
	for ( int i = 0; i < MAX_EVENT; i++ ) {
		if ( filename[ i ].empty( ) ) {
			continue;
		}
		BinaryPtr binary( new Binary );
		if ( !app->loadBinary( filename[ i ], binary ) ) {
			continue;
		}
		int tmp_page_num = 0;
		binary->read( (void*)&tmp_page_num, sizeof( int ) );

		int size = (int)( sizeof( unsigned char ) *
			tmp_page_num * PAGE_OBJECT_WIDTH_NUM * PAGE_OBJECT_WIDTH_NUM );

		unsigned char object;
		for ( int j = 0; j < size; j++ ) {
			binary->read( (void*)&object, sizeof( unsigned char ) );
			_objects[ i ][ j ] = object;
		}
	}
}

void MapEvent::update( ) {
	// 同期データにイベント情報を設定
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->setEvent( _event );
}

void MapEvent::setEvent( EVENT event ) {
	_event = event;
}

EVENT MapEvent::getEvent( ) const {
	return _event;
}

unsigned char MapEvent::getObject( const Vector& pos ) const {
	int mx = ( int )pos.x / OBJECT_CHIP_SIZE;
	int my = ( int )pos.y / OBJECT_CHIP_SIZE;
	unsigned char obj = getObject( mx, my );
	return obj;
}

unsigned char MapEvent::getObject( int mx, int my ) const {
	if ( my < 0 ) {
		return OBJECT_NONE;
	}
	if ( my >= OBJECT_CHIP_HEIGHT_NUM ) {
		return OBJECT_BLOCK;
	}

	unsigned char obj = OBJECT_NONE;
	int type = -1;
	switch ( _event ) {
	case EVENT_REDDAEMON:
		mx = ( mx + EVENT_PAGE_NUM * PAGE_OBJECT_WIDTH_NUM ) % ( EVENT_PAGE_NUM * PAGE_OBJECT_WIDTH_NUM );
		type = 0;
		break;
	case EVENT_FIRE:
		while ( mx >= EVENT_PAGE_NUM * PAGE_OBJECT_WIDTH_NUM ) {
			mx -= PAGE_OBJECT_WIDTH_NUM;
		}
		type = 1;
		break;
	case EVENT_TREE:
		while ( mx >= EVENT_PAGE_NUM * PAGE_OBJECT_WIDTH_NUM ) {
			mx -= PAGE_OBJECT_WIDTH_NUM;
		}
		type = 2;
		break;
	case EVENT_ROCK:
		while ( mx >= EVENT_PAGE_NUM * PAGE_OBJECT_WIDTH_NUM ) {
			mx -= PAGE_OBJECT_WIDTH_NUM;
		}
		type = 3;
		break;
	case EVENT_SHOP:
		while ( mx >= EVENT_PAGE_NUM * PAGE_OBJECT_WIDTH_NUM ) {
			mx -= PAGE_OBJECT_WIDTH_NUM;
		}
		type = 4;
	case EVENT_RYUGU:
		while ( mx >= EVENT_PAGE_NUM * PAGE_OBJECT_WIDTH_NUM ) {
			mx -= PAGE_OBJECT_WIDTH_NUM;
		}
		type = 5;
		break;
	case EVENT_LAKE:
		while ( mx >= EVENT_PAGE_NUM * PAGE_OBJECT_WIDTH_NUM ) {
			mx -= PAGE_OBJECT_WIDTH_NUM;
		}
		type = 6;
		break;
	case EVENT_GAMBLE:
		while ( mx >= EVENT_PAGE_NUM * PAGE_OBJECT_WIDTH_NUM ) {
			mx -= PAGE_OBJECT_WIDTH_NUM;
		}
		type = 7;
		break;
	}
	assert( mx >= 0 && mx < EVENT_PAGE_NUM * PAGE_OBJECT_WIDTH_NUM );
	int idx = mx + my * ( EVENT_PAGE_NUM * PAGE_OBJECT_WIDTH_NUM );
	obj = _objects[ type ][ idx ];
	return obj;
}