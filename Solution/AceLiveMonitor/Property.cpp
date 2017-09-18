#include "Property.h"
#include "Application.h"
#include <assert.h>

const int MAX_DATA_NUM = 100;
const std::string FILENAME = "Resource/Ace/Enemy/Property.csv";

PropertyPtr Property::getTask( ) {
	return std::dynamic_pointer_cast< Property >( Application::getInstance( )->getTask( getTag( ) ) );
}

Property::Property( ) {
	FILE* fp;
	errno_t file_load;
	file_load = fopen_s( &fp, FILENAME.c_str( ), "r" );

	assert( !file_load );

	char buffer[ 256 ];
	while ( fgets( buffer, 256, fp ) != NULL ) {
		//�s������
		std::string filename = buffer;
		//�J���}�̈ʒu���擾
		int index = ( int )filename.find(",");
		//���ڂ�tag
		std::string tag = filename.substr( 0, index );
		//�Q�ڂ̃J���}�̈ʒu���擾
		index = ( int )filename.find( ",", 2 );
		//���ڂ͒l
		int value = std::atoi( filename.substr( index + 1 ).c_str( ) );

		//�f�[�^��o�^
		_data[ tag ] = value;
	}
}


Property::~Property( ) {
}

void Property::initialize( ) {
}


void Property::update( ) {
	
}

int Property::getData( std::string tag ) {
	if ( _data.find( tag ) == _data.end( ) ) {
		assert( -1 );
		return 0;
	}
	return _data[ tag ];
}



