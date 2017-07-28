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
		_objects[i] = OBJECT_NONE;
		if ( i / ( _page_num * PAGE_OBJECT_WIDTH_NUM ) > OBJECT_CHIP_HEIGHT_NUM - 3 ) {
			_objects[ i ] = OBJECT_BLOCK;
		}
	}
	_bg.resize( _page_num );
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

std::string Data::getBg( int page ) const {
	return _bg[ page ];
}


int Data::getPageNum( ) const {
	return _page_num;
}

void Data::insert( int page ) {
	{//chip
		std::vector< Chip > chips;
		//�}���n�_
		int insert_pos = page * PAGE_CHIP_WIDTH_NUM;
		//�y�[�W�ǉ��O�̉��̐�
		int chip_width_num_old = _page_num * PAGE_CHIP_WIDTH_NUM;
		//�y�[�W�ǉ���̐�
		int chip_width_num_new = ( _page_num + 1 ) * PAGE_CHIP_WIDTH_NUM;
		//���T�C�Y
		int max_new = chip_width_num_new * MAP_HEIGHT;
		chips.resize( max_new );
		//chip������
		for ( int i = 0; i < max_new; i++ ) {
			chips[ i ] = Chip( );
			chips[ i ].ground = 0;
		}
		//���
		for ( int i = 0; i < chip_width_num_new; i++ ) {
			int mx = i;
			if ( mx >= insert_pos && mx < insert_pos + PAGE_CHIP_WIDTH_NUM ) {
				//�}���n�_�̓X���[����
				continue;
			}
			int mx_old = mx;
			if ( mx > insert_pos ) {
				mx_old -= PAGE_CHIP_WIDTH_NUM;
			}
			for ( int j = 0; j < MAP_HEIGHT; j++ ) {
				int my = j;
				int idx = chip_width_num_new * my + mx;
				chips[ idx ] = getChip( mx_old, my );
			}
		}
		_chips = chips;
	}

	{//object
		std::vector< unsigned char > objects;
		//�}���n�_
		int insert_pos = page * PAGE_OBJECT_WIDTH_NUM;
		//�y�[�W�ǉ��O�̉��̐�
		int width_num_old = _page_num * PAGE_OBJECT_WIDTH_NUM;
		//�y�[�W�ǉ���̉��̐�
		int width_num_new = ( _page_num + 1 ) * PAGE_OBJECT_WIDTH_NUM;
		//�y�[�W�ǉ���̃T�C�Y
		int max_new = width_num_new * OBJECT_CHIP_HEIGHT_NUM;
		//���T�C�Y
		objects.resize( max_new );
		//�z�񏉊���
		for ( int i = 0; i < max_new; i++ ) {
			objects[ i ] = OBJECT_NONE;
		}
		//���
		for ( int i = 0; i < width_num_new; i++ ) {
			int ox = i;
			if ( ox >= insert_pos && ox < insert_pos + PAGE_OBJECT_WIDTH_NUM ) {
				//�}���n�_�̓X���[����
				continue;
			}
			int ox_old = ox;
			if ( ox > insert_pos ) {
				ox_old -= PAGE_OBJECT_WIDTH_NUM;
			}
			for ( int j = 0; j < OBJECT_CHIP_HEIGHT_NUM; j++ ) {
				int oy = j;
				int idx = ox + width_num_new * oy;
				objects[ idx ] = getObject( ox_old, oy );
			}
		}
		_objects = objects;
	}
	{//bg
		std::vector< std::string > bg;
		bg.resize( _page_num + 1 );
		for ( int i = 0; i < _page_num + 1; i++ ) {
			int page_old = i;
			int page_new = i;
			if ( i == page ) {
				continue;
			}
			if ( i > page ) {
				page_old--;
			}
			bg[ page_new ] = _bg[ page_old ];
		}
		_bg = bg;
	}
	//�y�[�W���ЂƂ��₷(get�n�֐��ɉe������̂ōŌ�ɍs��)
	_page_num++;
}

void Data::erase( int page ) {
	if ( _page_num <= 1 ) {
		return;
	}
	{//chip
		std::vector< Chip > chips;
		//�폜�n�_
		int erase_pos = page * PAGE_CHIP_WIDTH_NUM;
		//�y�[�W�폜�O�̉��̐�
		int width_num_old = _page_num * PAGE_CHIP_WIDTH_NUM;
		//�y�[�W�폜��̉��̐�
		int width_num_new = ( _page_num - 1 ) * PAGE_CHIP_WIDTH_NUM;
		//�y�[�W�폜��̃T�C�Y
		int max_new = width_num_new * MAP_HEIGHT;
		//���T�C�Y
		chips.resize( max_new );

		//�z�񏉊���
		for ( int i = 0; i < max_new; i++ ) {
			chips[ i ] = Chip( );
		}

		//�}���ʒu�܂ő��
		for ( int i = 0; i < width_num_old; i++ ) {
			int mx_old = i;
			if ( mx_old >= erase_pos && mx_old < erase_pos + PAGE_CHIP_WIDTH_NUM ) {
				//�폜�n�_�̓X���[
				continue;
			}
			int mx = i;
			if ( mx_old > erase_pos ) {
				//�폜��mx�����炷
				mx -= PAGE_CHIP_WIDTH_NUM;
			}
			for ( int j = 0; j < MAP_HEIGHT; j++ ) {
				int my = j;
				int idx = width_num_new * my + mx;
				chips[ idx ] = getChip( mx_old, my );
			}
		}
		_chips = chips;
	}

	{//object
		std::vector< unsigned char > objects;
		//�폜�n�_
		int erase_pos = page * PAGE_OBJECT_WIDTH_NUM;
		//�y�[�W�폜�O�̉��̐�
		int width_num_old = _page_num * PAGE_OBJECT_WIDTH_NUM;
		//�y�[�W�폜��̉��̐�
		int width_num_new = ( _page_num - 1 ) * PAGE_OBJECT_WIDTH_NUM;
		//�y�[�W�폜��̃T�C�Y
		int max_new = width_num_new * OBJECT_CHIP_HEIGHT_NUM;
		//���T�C�Y
		objects.resize( max_new );

		//�z�񏉊���
		for ( int i = 0; i < max_new; i++ ) {
			objects[ i ] = OBJECT_NONE;
		}

		//�}���ʒu�܂ő��
		for ( int i = 0; i < width_num_old; i++ ) {
			int ox_old = i;
			if ( ox_old >= erase_pos && ox_old < erase_pos + PAGE_OBJECT_WIDTH_NUM ) {
				//�폜�n�_�̓X���[
				continue;
			}
			int ox = i;
			if ( ox_old > erase_pos ) {
				//�폜��ox�����炷
				ox -= PAGE_OBJECT_WIDTH_NUM;
			}
			for ( int j = 0; j < OBJECT_CHIP_HEIGHT_NUM; j++ ) {
				int oy = j;
				int idx = width_num_new * oy + ox;
				objects[ idx ] = getObject( ox_old, oy );
			}
		}
		_objects = objects;
	}
	{//bg
		std::vector< std::string > bg;
		bg.resize( _page_num - 1 );
		for ( int i = 0; i < _page_num; i++ ) {
			int page_old = i;
			int page_new = i;
			if ( i == page ) {
				continue;
			}
			if ( i > page ) {
				page_new--;
			}
			bg[ page_new ] = _bg[ page_old ];
		}
		_bg = bg;
	}
	//�y�[�W���ЂƂ��炷(get�n�֐��ɉe������̂ōŌ�ɍs��)
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
	_bg.resize( _page_num );
}


void Data::savePage( std::string directory, std::string filename, int page ) const {

	if ( filename.find( EXTENSION_PAGE ) == std::string::npos ) {
		filename += EXTENSION_PAGE;
	}
	std::vector< Chip > page_chip;
	int max_chip = PAGE_CHIP_WIDTH_NUM * MAP_HEIGHT;
	page_chip.resize( max_chip );

	std::vector< unsigned char > page_object;
	int max_object = PAGE_OBJECT_WIDTH_NUM * OBJECT_CHIP_HEIGHT_NUM;
	page_object.resize( max_object );

	int base_chip_mx = page * PAGE_CHIP_WIDTH_NUM;
	int base_chip_my = 0;
	for ( int i = 0; i < MAP_HEIGHT; i++ ) {
		int my = base_chip_my + i;
		int y = i;
		for ( int j = 0; j < PAGE_CHIP_WIDTH_NUM; j++ ) {
			int mx = base_chip_mx + j;
			int x = j;
			int page_chip_idx = x + y * PAGE_CHIP_WIDTH_NUM;
			int chips_idx = mx + my * _page_num * PAGE_CHIP_WIDTH_NUM;
			page_chip[ page_chip_idx ] = _chips[ chips_idx ];
		}
	}

	int base_obj_mx = page * PAGE_OBJECT_WIDTH_NUM;
	int base_obj_my = 0;
	for ( int i = 0; i < OBJECT_CHIP_HEIGHT_NUM; i++ ) {
		int my = base_obj_my + i;
		int y = i;
		for ( int j = 0; j < PAGE_OBJECT_WIDTH_NUM; j++ ) {
			int mx = base_obj_mx + j;
			int x = j;
			int page_obj_idx = x + y * PAGE_OBJECT_WIDTH_NUM;
			int objects_idx = mx + my * _page_num * PAGE_OBJECT_WIDTH_NUM;
			page_object[ page_obj_idx ] = _objects[ objects_idx ];
		}
	}

	BinaryPtr binary( new Binary );
	int chip_size = (int)( sizeof( Chip ) * max_chip );
	int obj_size = (int)( sizeof( unsigned char ) * max_object );

	binary->ensure( chip_size + obj_size + sizeof( int ) * 2 );
		
	binary->write( (void*)&chip_size         , sizeof( int ) );
	binary->write( (void*)&obj_size          , sizeof( int ) );
	binary->write( (void*)page_chip.data( )  , chip_size     );
	binary->write( (void*)page_object.data( ), obj_size      );

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
	int max_chip = PAGE_CHIP_WIDTH_NUM * MAP_HEIGHT;
	page_chip.resize( max_chip );

	std::vector< unsigned char > page_object;
	int max_object = PAGE_OBJECT_WIDTH_NUM * OBJECT_CHIP_HEIGHT_NUM;
	page_object.resize( max_object );
		
	int page_size_chip;
	binary->read( (void*)&page_size_chip, sizeof( int ) );

	int page_size_object;
	binary->read( (void*)&page_size_object, sizeof( int ) );

	binary->read( (void*)page_chip.data( ), page_size_chip );
	binary->read( (void*)page_object.data( ), page_size_object );

	int base_chip_mx = page * PAGE_CHIP_WIDTH_NUM;
	int base_chip_my = 0;
	for ( int i = 0; i < MAP_HEIGHT; i++ ) {
		int my = base_chip_my + i;
		int y = i;
		for ( int j = 0; j < PAGE_CHIP_WIDTH_NUM; j++ ) {
			int mx = base_chip_mx + j;
			int x = j;
			int page_chip_idx = x + y * PAGE_CHIP_WIDTH_NUM;
			int chips_idx = mx + my * _page_num * PAGE_CHIP_WIDTH_NUM;
			_chips[ chips_idx ] = page_chip[ page_chip_idx ];
		}
	}

	int base_obj_mx = page * PAGE_OBJECT_WIDTH_NUM;
	int base_obj_my = 0;
	for ( int i = 0; i < OBJECT_CHIP_HEIGHT_NUM; i++ ) {
		int my = base_obj_my + i;
		int y = i;
		for ( int j = 0; j < PAGE_OBJECT_WIDTH_NUM; j++ ) {
			int mx = base_obj_mx + j;
			int x = j;
			int page_obj_idx = x + y * PAGE_OBJECT_WIDTH_NUM;
			int objects_idx = mx + my * _page_num * PAGE_OBJECT_WIDTH_NUM;
			_objects[ objects_idx ] = page_object[ page_obj_idx ];
		}
	}

}

void Data::loadBg( std::string directory, std::string filename, int page ) {
	if ( page >= ( int )_bg.size( ) ) {
		return;
	}
	_bg[ page ] = filename;
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
