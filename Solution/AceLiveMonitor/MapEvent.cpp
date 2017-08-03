#include "MapEvent.h"
#include "Application.h"
#include <assert.h>
#include "Binary.h"
#include "Military.h"

const std::string FILENAME[ MAX_EVENT ] {
	"Resource/Ace/Event/akaoni/mapdata",//red deamon
	"",
	"",
	"",
	"",
	""
};

MapEventPtr MapEvent::getTask( ) {
	return std::dynamic_pointer_cast< MapEvent >( Application::getInstance( )->getTask( getTag( ) ) );
}


MapEvent::MapEvent( ) {
	_type = ViewerEvent::TYPE_TITLE;
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
}

void MapEvent::setType( ViewerEvent::TYPE type ) {
	_type = type;
	Military::getTask( )->createBoss( );
}

ViewerEvent::TYPE  MapEvent::getType( ) const {
	return _type;
}

unsigned char MapEvent::getObject( const Vector& pos ) const {
	int object_width_num = EVENT_PAGE_NUM * PAGE_OBJECT_WIDTH_NUM;
	int x = ( ( int )pos.x / OBJECT_CHIP_SIZE + object_width_num ) % object_width_num;
	int y = ( int )pos.y / OBJECT_CHIP_SIZE;
	unsigned char obj = getObject( x, y );
	return obj;
}

unsigned char MapEvent::getObject( int mx, int my ) const {
	assert( mx >= 0 && mx < EVENT_PAGE_NUM * PAGE_OBJECT_WIDTH_NUM && my < OBJECT_CHIP_HEIGHT_NUM );
	int idx = mx + my * ( EVENT_PAGE_NUM * PAGE_OBJECT_WIDTH_NUM );
	unsigned char obj = OBJECT_NONE;
	switch ( _type ) {
	case ViewerEvent::TYPE_TITLE:
		break;
	case ViewerEvent::TYPE_RED_DEMON:
		obj = _objects[ 0 ][ idx ];
		break;
	}
	return obj;
}