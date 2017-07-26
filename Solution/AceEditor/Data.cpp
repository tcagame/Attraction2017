#include "Data.h"
#include "Application.h"
#include "Binary.h"
#include "ace_define.h"
#include <direct.h>

std::string EXTENSION_ALL  = ".map";
std::string EXTENSION_PAGE = ".page";

Data::Data( ) {
	_page_num = 4;
	int max_chip = _page_num * PAGE_CHIP_WIDTH_NUM * MAP_HEIGHT;
	_chips.resize( max_chip );
	for ( int i = 0; i < max_chip; i++ ) {
		_chips[ i ].ground = 1;
		_chips[ i ].structure = 0;
		_chips[ i ].height = 0;
	}
	const int MAX_OBJ = _page_num * PAGE_OBJECT_WIDTH_NUM * OBJECT_CHIP_HEIGHT_NUM;
	_objects.resize( MAX_OBJ );
	for ( int i = 0; i < MAX_OBJ; i++ ) {
		_objects[ i ] = (unsigned char)( i % 5 );
	}
}

Data::~Data( ) {
	_chips.clear( );
}

int Data::getGround( int mx, int my ) const {
	return getChip( mx, my ).ground;
}

int Data::getStructure( int mx, int my ) const {
	return getChip( mx, my ).structure;
}

int Data::getHeight( int mx, int my ) const {
	return getChip( mx, my ).height;
}

void Data::setHeight( int mx, int my, int height ) {
	mx %= _page_num * PAGE_CHIP_WIDTH_NUM;
	getChip( mx, my ).height = height;
}

void Data::setStructure( int mx, int my, int num )  {
	mx %= _page_num * PAGE_CHIP_WIDTH_NUM;
	getChip( mx, my ).structure = num;
}

void Data::setGroundData( int mx, int my, int num ) {
	mx %= _page_num * PAGE_CHIP_WIDTH_NUM;
	getChip( mx, my ).ground = num;
}

void Data::setObject( int ox, int oy, unsigned char object ) {
	ox %= _page_num * PAGE_OBJECT_WIDTH_NUM;
	_objects[ ox + oy * _page_num * PAGE_OBJECT_WIDTH_NUM ] = object;
}

const Data::Chip& Data::getChip( int mx, int my ) const {
	return _chips[ mx + my * _page_num * PAGE_CHIP_WIDTH_NUM ];
}

Data::Chip& Data::getChip( int mx, int my ) {
	return _chips[ mx + my * _page_num * PAGE_CHIP_WIDTH_NUM ];
}

unsigned char Data::getObject( int ox, int oy ) const {
	return _objects[ ox + oy * _page_num * PAGE_OBJECT_WIDTH_NUM ];
}

int Data::getPageNum( ) const {
	return _page_num;
}

void Data::insert( int page ) {
	std::vector< Chip > chips;
	int new_max_chip = ( _page_num + 1 ) * PAGE_CHIP_WIDTH_NUM * MAP_HEIGHT;
	chips.resize( new_max_chip );
	int old_chip_width_num = _page_num * PAGE_CHIP_WIDTH_NUM;
	int new_chip_width_num = ( _page_num + 1 ) * PAGE_CHIP_WIDTH_NUM;
	int front_chip_width_num = page * PAGE_CHIP_WIDTH_NUM;

	std::vector< unsigned char > objects;
	int new_max_object = ( _page_num + 1 ) * PAGE_OBJECT_WIDTH_NUM * OBJECT_CHIP_HEIGHT_NUM;
	objects.resize( new_max_object );
	int old_object_width_num = _page_num * PAGE_OBJECT_WIDTH_NUM;
	int new_object_width_num = ( _page_num + 1 ) * PAGE_OBJECT_WIDTH_NUM;
	int front_object_width_num = page * PAGE_OBJECT_WIDTH_NUM;

	//初期化
	for ( int i = 0; i < new_chip_width_num * MAP_HEIGHT; i++ ) {
		chips[ i ] = Chip( );
		chips[ i ].ground = 1;
	}
	for ( int i = 0; i < new_object_width_num * OBJECT_CHIP_HEIGHT_NUM; i++ ) {
		objects[ i ] = OBJECT_NONE;
	}

	//挿入位置まで代入
	for ( int i = 0; i < front_chip_width_num; i++ ) {
		int mx = i;
		for ( int j = 0; j < MAP_HEIGHT; j++ ) {
			int my = j;
			int idx = new_chip_width_num * my + mx;
			chips[ idx ] = getChip( mx, my );
		}
	}
	for ( int i = 0; i < front_object_width_num; i++ ) {
		for ( int j = 0; j < OBJECT_CHIP_HEIGHT_NUM; j++ ) {
			int ox = i;
			int oy = j;
			int idx = ox + new_object_width_num * oy;
			objects[ idx ] = getObject( ox, oy );
		}
	}

	//挿入位置の一ページ後から代入
	int back_chip_start_width_num = front_chip_width_num;
	for ( int i = back_chip_start_width_num; i < old_chip_width_num; i++ ) {
		int mx = i;
		for ( int j = 0; j < MAP_HEIGHT; j++ ) {
			int my = j;
			int idx = new_chip_width_num * my + ( mx + PAGE_CHIP_WIDTH_NUM );
			chips[ idx ] = getChip( mx, my );
		}
	}
	int back_object_start_width_num = front_object_width_num;
	for ( int i = back_object_start_width_num; i < old_object_width_num; i++ ) {
		for ( int j = 0; j < OBJECT_CHIP_HEIGHT_NUM; j++ ) {
			int ox = i;
			int oy = j;
			int idx = ( ox + PAGE_OBJECT_WIDTH_NUM ) + new_object_width_num * oy;
			objects[ idx ] = getObject( ox, oy );
		}
	}
	_chips = chips;
	_objects = objects;
	_page_num++;
}

void Data::erase( int page ) {
	if ( _page_num <= 1 ) {
		return;
	}
	std::vector< Chip > chips;
	int new_max_chip = ( _page_num - 1 ) * PAGE_CHIP_WIDTH_NUM * MAP_HEIGHT;
	chips.resize( new_max_chip );
	int new_width_num = ( _page_num - 1 ) * PAGE_CHIP_WIDTH_NUM;
	int front_width_num = page * PAGE_CHIP_WIDTH_NUM;

	//初期化
	for ( int i = 0; i < new_width_num * MAP_HEIGHT; i++ ) {
		chips[ i ] = Chip( );
	}

	//挿入位置まで代入
	for ( int i = 0; i < front_width_num; i++ ) {
		int mx = i;
		for ( int j = 0; j < MAP_HEIGHT; j++ ) {
			int my = j;
			int idx = new_width_num * my + mx;
			chips[ idx ] = getChip( mx, my );
		}
	}
	int old_width_num = _page_num * PAGE_CHIP_WIDTH_NUM;
	int back_start_width_num = front_width_num + PAGE_CHIP_WIDTH_NUM;
	for ( int i = back_start_width_num; i < old_width_num; i++ ) {
		int mx = i;
		for ( int j = 0; j < MAP_HEIGHT; j++ ) {
			int my = j;
			int idx = new_width_num * my + ( mx - PAGE_CHIP_WIDTH_NUM );
			chips[ idx ] = getChip( mx, my );
		}
	}

	_chips = chips;
	_page_num--;
}

void Data::save( std::string directory, std::string filename ) const {
	
	_mkdir( directory.c_str( ) );

	if ( filename.find( EXTENSION_ALL ) == std::string::npos ) {
		filename += EXTENSION_ALL;
	}

	filename = directory + filename;

	BinaryPtr binary( new Binary );

	int size_chip   = (int)( sizeof( Chip          ) * _chips.size( ) );
	int size_object = (int)( sizeof( unsigned char ) * _objects.size( ) );
	binary->ensure( size_chip + size_object + sizeof( int ) * 2 );
	
	binary->write( (void*)&size_chip      , sizeof( int ) );
	binary->write( (void*)&size_object    , sizeof( int ) );
	binary->write( (void*)_chips.data( )  , size_chip     );
	binary->write( (void*)_objects.data( ), size_object   );

	ApplicationPtr app( Application::getInstance( ) );
	app->saveBinary( filename, binary );
}

void Data::load( std::string directory, std::string filename ) {

	if ( filename.find( EXTENSION_ALL ) == std::string::npos ) {
		filename += EXTENSION_ALL;
	}

	filename = directory + filename;

	BinaryPtr binary( new Binary );

	ApplicationPtr app( Application::getInstance( ) );
	if ( !app->loadBinary( filename, binary ) ) {
		return;
	}
	
	int size_chip;
	binary->read( (void*)&size_chip, sizeof( int ) );

	int size_object;
	binary->read( (void*)&size_object, sizeof( int ) );

	_chips.resize( size_chip / sizeof( Chip ) );
	binary->read( (void*)_chips.data( ), size_chip );

	_objects.resize( size_object / sizeof( unsigned char ) );
	binary->read( (void*)_objects.data( ), size_object );

	int width = ( int )( _chips.size( ) / MAP_HEIGHT );
	_page_num = width / PAGE_CHIP_WIDTH_NUM;
}


void Data::savePage( std::string directory, std::string filename, int page ) const {

	if ( filename.find( EXTENSION_PAGE ) == std::string::npos ) {
		filename += EXTENSION_PAGE;
	}
	std::vector< Chip > page_chip;
	int max = PAGE_CHIP_WIDTH_NUM * MAP_HEIGHT;
	page_chip.resize( max );
	int base_mx = page * PAGE_CHIP_WIDTH_NUM;
	int base_my = 0;
	for ( int i = 0; i < MAP_HEIGHT; i++ ) {
		int my = base_my + i;
		int y = i;
		for ( int j = 0; j < PAGE_CHIP_WIDTH_NUM; j++ ) {
			int mx = base_mx + j;
			int x = j;
			int page_chip_idx = x + y * PAGE_CHIP_WIDTH_NUM;
			int chips_idx = mx + my * _page_num * PAGE_CHIP_WIDTH_NUM;
			page_chip[ page_chip_idx ] = _chips[ chips_idx ];
		}
	}
	BinaryPtr binary( new Binary );
	int size = (int)( sizeof( Chip ) * max );
	binary->ensure( size );
	binary->write( (void*)page_chip.data( ), size );
	ApplicationPtr app( Application::getInstance( ) );
	app->saveBinary( filename, binary );
}

void Data::loadPage( std::string directory, std::string filename, int page ) {
	if ( filename.find( EXTENSION_PAGE ) == std::string::npos ) {
		filename += EXTENSION_PAGE;
	}
	BinaryPtr binary( new Binary );
	ApplicationPtr app( Application::getInstance( ) );
	if ( !app->loadBinary( filename, binary ) ) {
		return;
	}

	std::vector< Chip > page_chip;
	int max = PAGE_CHIP_WIDTH_NUM * MAP_HEIGHT;
	page_chip.resize( max );
	binary->read( (void*)page_chip.data( ), binary->getSize( ) );

	int base_mx = page * PAGE_CHIP_WIDTH_NUM;
	int base_my = 0;
	for ( int i = 0; i < MAP_HEIGHT; i++ ) {
		int my = base_my + i;
		int y = i;
		for ( int j = 0; j < PAGE_CHIP_WIDTH_NUM; j++ ) {
			int mx = base_mx + j;
			int x = j;
			int page_chip_idx = x + y * PAGE_CHIP_WIDTH_NUM;
			int chips_idx = mx + my * _page_num * PAGE_CHIP_WIDTH_NUM;
			_chips[ chips_idx ] = page_chip[ page_chip_idx ];
		}
	}
}

void Data::copy( std::vector< int >& mx, std::vector< int >& my ) {
	_copy = { };
	int size = (int)mx.size( );
	_copy.resize( size );
	for ( int i = 0; i < size; i++ ) {
		mx[ i ] %= _page_num * PAGE_CHIP_WIDTH_NUM;
		if ( my[ i ] < 0 || mx[ i ] < 0 ) {
			continue;
		}
		_copy[ i ] = getChip( mx[ i ], my[ i ] );
	}
}

void Data::paste( std::vector< int >& mx, std::vector< int >& my ) {
	int size = (int)mx.size( );
	for ( int i = 0; i < size; i++ ) {
		mx[ i ] %= _page_num * PAGE_CHIP_WIDTH_NUM;
		if ( my[ i ] < 0 || mx[ i ] < 0 ) {
			continue;
		}
		getChip( mx[ i ], my[ i ] ) = _copy[ i ];
	}
}
