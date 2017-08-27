#include "MapEvent.h"
#include "Application.h"
#include "Binary.h"
#include "SynchronousData.h"
#include <assert.h>

const std::string FILENAME[ MAX_EVENT ] {
	"Resource/Ace/Event/akaoni/mapdata",//red deamon
	"Resource/Ace/Event/fire/mapdata",  //fire
	"Resource/Ace/Event/tree/mapdata",	//tree
	"Resource/Ace/Event/rock/mapdata",	//rock
	"Resource/Ace/Event/shop/mapdata",  //shop
	"Resource/Ace/Event/ryugu/mapdata", //ryugu
	"Resource/Ace/Event/lake/mapdata",  //lake
	"Resource/Ace/Event/gamble/mapdata",  //gamble
};

MapEventPtr MapEvent::getTask( ) {
	return std::dynamic_pointer_cast< MapEvent >( Application::getInstance( )->getTask( getTag( ) ) );
}


MapEvent::MapEvent( ) {
	_type = TYPE_TITLE;
	_objects = { };
	load( );
}


MapEvent::~MapEvent( ) {
}


void MapEvent::load( ) {
	ApplicationPtr app( Application::getInstance( ) );
	for ( int i = 0; i < MAX_EVENT; i++ ) {
		BinaryPtr binary( new Binary );
		if ( !app->loadBinary( FILENAME[ i ], binary ) ) {
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
	EVENT event = EVENT_NONE;
	switch ( _type ) {
	case TYPE_RED_DAEMON: event = EVENT_REDDAEMON; break;
	case TYPE_FIRE      : event = EVENT_FIRE     ; break;
	case TYPE_TREE      : event = EVENT_TREE     ; break;
	case TYPE_ROCK   	: event = EVENT_ROCK     ; break;
	case TYPE_SHOP   	: event = EVENT_SHOP     ; break;
	case TYPE_RYUGU  	: event = EVENT_RYUGU    ; break;
	case TYPE_LAKE   	: event = EVENT_LAKE     ; break;
	case TYPE_GAMBLE    : event = EVENT_GAMBLE   ; break; 
	}

	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->setEvent( event );
}

void MapEvent::setType( TYPE type ) {
	_type = type;
}

MapEvent::TYPE MapEvent::getType( ) const {
	return _type;
}

unsigned char MapEvent::getObject( const Vector& pos ) const {
	int mx = ( int )pos.x / OBJECT_CHIP_SIZE;
	int my = ( int )pos.y / OBJECT_CHIP_SIZE;
	unsigned char obj = getObject( mx, my );
	return obj;
}

unsigned char MapEvent::getObject( int mx, int my ) const {
	unsigned char obj = OBJECT_NONE;
	int type = -1;
	switch ( _type ) {
	case TYPE_TITLE:
		break;
	case TYPE_RED_DAEMON:
		mx = ( mx + EVENT_PAGE_NUM * PAGE_OBJECT_WIDTH_NUM ) % ( EVENT_PAGE_NUM * PAGE_OBJECT_WIDTH_NUM );
		type = 0;
		break;
	case TYPE_FIRE:
		while ( mx >= EVENT_PAGE_NUM * PAGE_OBJECT_WIDTH_NUM ) {
			mx -= PAGE_OBJECT_WIDTH_NUM;
		}
		type = 1;
		break;
	case TYPE_TREE:
		while ( mx >= EVENT_PAGE_NUM * PAGE_OBJECT_WIDTH_NUM ) {
			mx -= PAGE_OBJECT_WIDTH_NUM;
		}
		type = 2;
		break;
	case TYPE_ROCK:
		while ( mx >= EVENT_PAGE_NUM * PAGE_OBJECT_WIDTH_NUM ) {
			mx -= PAGE_OBJECT_WIDTH_NUM;
		}
		type = 3;
		break;
	case TYPE_SHOP:
		while ( mx >= EVENT_PAGE_NUM * PAGE_OBJECT_WIDTH_NUM ) {
			mx -= PAGE_OBJECT_WIDTH_NUM;
		}
		type = 4;
	case TYPE_RYUGU:
		while ( mx >= EVENT_PAGE_NUM * PAGE_OBJECT_WIDTH_NUM ) {
			mx -= PAGE_OBJECT_WIDTH_NUM;
		}
		type = 5;
		break;
	case TYPE_LAKE:
		while ( mx >= EVENT_PAGE_NUM * PAGE_OBJECT_WIDTH_NUM ) {
			mx -= PAGE_OBJECT_WIDTH_NUM;
		}
		type = 6;
		break;
	case TYPE_GAMBLE:
		while ( mx >= EVENT_PAGE_NUM * PAGE_OBJECT_WIDTH_NUM ) {
			mx -= PAGE_OBJECT_WIDTH_NUM;
		}
		type = 7;
		break;
	}
	assert( mx >= 0 && mx < EVENT_PAGE_NUM * PAGE_OBJECT_WIDTH_NUM && my < OBJECT_CHIP_HEIGHT_NUM );
	int idx = mx + my * ( EVENT_PAGE_NUM * PAGE_OBJECT_WIDTH_NUM );
	obj = _objects[ type ][ idx ];
	return obj;
}