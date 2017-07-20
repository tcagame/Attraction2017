#include "Data.h"
#include "Application.h"
#include "Binary.h"
#include "ace_define.h"

std::string EXTENSION_ALL  = ".map";
std::string EXTENSION_PAGE = ".page";

Data::Data( ) {
	_page_num = 4;
	int max_chip = _page_num * PAGE_CHIP_WIDTH_NUM * MAP_HEIGHT;
	_chips.resize( max_chip );
	for ( int i = 0; i < max_chip; i++ ) {
		//_chips[ i ].ground = ( i % ( PAGE_NUM * PAGE_CHIP_WIDTH_NUM ) % 4 == 0 && ( i / ( PAGE_NUM * PAGE_CHIP_WIDTH_NUM ) ) % 2 == 0 );
		_chips[ i ].ground = i % 6;
		_chips[ i ].structure = i % 7;
		_chips[ i ].height = ( i / 7 ) % 9;
	}
}


Data::~Data( ) {
	_chips.clear( );
}

int Data::getGroundData( int mx, int my ) const {
	return getChip( mx, my ).ground;
}

int Data::getStructureData( int mx, int my ) const {
	return getChip( mx, my ).structure;
}

int Data::getHeightData( int mx, int my ) const {
	return getChip( mx, my ).height;
}

void Data::setHeightData( int mx, int my, int height ) {
	mx %= _page_num * PAGE_CHIP_WIDTH_NUM;
	getChip( mx, my ).height = height;
}

void Data::setStructureData( int mx, int my, int num )  {
	mx %= _page_num * PAGE_CHIP_WIDTH_NUM;
	getChip( mx, my ).structure = num;
}

void Data::setGroundData( int mx, int my, int num ) {
	mx %= _page_num * PAGE_CHIP_WIDTH_NUM;
	getChip( mx, my ).ground = num;
}

const Data::Chip& Data::getChip( int mx, int my ) const {
	return _chips[ mx + my * _page_num * PAGE_CHIP_WIDTH_NUM ];
}

Data::Chip& Data::getChip( int mx, int my ) {
	return _chips[ mx + my * _page_num * PAGE_CHIP_WIDTH_NUM ];
}

int Data::getPageNum( ) const {
	return _page_num;
}


void Data::insert( int page ) {
	std::vector< Chip > chips;
	int new_max_chip = ( _page_num + 1 ) * PAGE_CHIP_WIDTH_NUM * MAP_HEIGHT;
	chips.resize( new_max_chip );
	int old_width_num = _page_num * PAGE_CHIP_WIDTH_NUM;
	int new_width_num = ( _page_num + 1 ) * PAGE_CHIP_WIDTH_NUM;
	int front_width_num = page * PAGE_CHIP_WIDTH_NUM;

	//������
	for ( int i = 0; i < new_width_num * MAP_HEIGHT; i++ ) {
		chips[ i ] = Chip( );
		chips[ i ].ground = 1;
	}

	//�}���ʒu�܂ő��
	for ( int i = 0; i < front_width_num; i++ ) {
		int mx = i;
		for ( int j = 0; j < MAP_HEIGHT; j++ ) {
			int my = j;
			int idx = new_width_num * my + mx;
			chips[ idx ] = getChip( mx, my );
		}
	}

	//�}���ʒu�̈�y�[�W�ォ����
	int back_start_width_num = front_width_num;
	for ( int i = back_start_width_num; i < old_width_num; i++ ) {
		int mx = i;
		for ( int j = 0; j < MAP_HEIGHT; j++ ) {
			int my = j;
			int idx = new_width_num * my + ( mx + PAGE_CHIP_WIDTH_NUM );
			chips[ idx ] = getChip( mx, my );
		}
	}

	_chips = chips;
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

	//������
	for ( int i = 0; i < new_width_num * MAP_HEIGHT; i++ ) {
		chips[ i ] = Chip( );
	}

	//�}���ʒu�܂ő��
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

void Data::save( std::string filename ) const {
	if ( filename.find( EXTENSION_ALL ) == std::string::npos ) {
		filename += EXTENSION_ALL;
	}
	BinaryPtr binary( new Binary );
	int size = (int)( sizeof( Chip ) * _chips.size( ) );
	binary->ensure( size );
	binary->write( (void*)_chips.data( ), size );
	ApplicationPtr app( Application::getInstance( ) );
	app->saveBinary( filename, binary );
}

void Data::load( std::string filename ) {
	if ( filename.find( EXTENSION_ALL ) == std::string::npos ) {
		filename += EXTENSION_ALL;
	}
	BinaryPtr binary( new Binary );
	ApplicationPtr app( Application::getInstance( ) );
	if ( !app->loadBinary( filename, binary ) ) {
		return;
	}
	_chips = { };
	int size = binary->getSize( ) / (int)( sizeof( Chip ) );
	_chips.resize( size );
	binary->read( (void*)_chips.data( ), binary->getSize( ) );
	int width = (int)( _chips.size( ) / MAP_HEIGHT );
	_page_num = width / PAGE_CHIP_WIDTH_NUM;
}


void Data::savePage( std::string filename, int page ) const {
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

void Data::loadPage( std::string filename, int page ) {
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
	//_copy = { };
}