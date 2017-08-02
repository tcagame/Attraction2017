#include "Map.h"
#include "Application.h"
#include "Binary.h"
#include "ace_define.h"
#include <assert.h>

const char * FILENAME = "Resource/Ace/Map/mapdata";

MapPtr Map::getTask( ) {
	return std::dynamic_pointer_cast< Map >( Application::getInstance( )->getTask( getTag( ) ) );
}


Map::Map( ) {
	load( );
}


Map::~Map( ) {
}

void Map::update( ) {

}

int Map::getPageNum( ) const {
	return _page_num;
}

void Map::load( ) {
	BinaryPtr binary( new Binary );
	ApplicationPtr app( Application::getInstance( ) );
	app->loadBinary( FILENAME, binary );
	
	binary->read( (void*)&_page_num, sizeof( int ) );

	int size = (int)( sizeof( unsigned char ) *
		_page_num * PAGE_OBJECT_WIDTH_NUM * PAGE_OBJECT_WIDTH_NUM );
	
	_objects.resize( size );

	unsigned char object;
	for ( int i = 0; i < size; i++ ) {
		binary->read( (void*)&object, sizeof( unsigned char ) );
		_objects[ i ] = object;
	}
}

unsigned char Map::getObject( const Vector& pos ) const {
	int object_width_num = _page_num * PAGE_OBJECT_WIDTH_NUM;
	int x = ( ( int )pos.x / OBJECT_CHIP_SIZE ) % object_width_num;
	int y = ( int )pos.y / OBJECT_CHIP_SIZE;
	unsigned char obj = getObject( x, y );
	return obj;
}

unsigned char Map::getObject( int mx, int my ) const {
	assert( mx >= 0 && mx < _page_num * PAGE_OBJECT_WIDTH_NUM && my < OBJECT_CHIP_HEIGHT_NUM );
	int idx = mx + my * ( _page_num * PAGE_OBJECT_WIDTH_NUM );
	return _objects[ idx ];
}