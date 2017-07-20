#include "Status.h"

Status::Status( ) {
}


Status::~Status( ) {
}

Status::STATUS::STATUS( ) :
state( 0x00000000 ),
continue_num( 0x00000000 ),
toku( 0x00000000 ),
item( 0x00000000 ),
money( 0x00000000 ),
power( 0x00000000 ) {
}

std::string Status::BToS( unsigned char b ) {
	std::string str;
	for ( int i = 0; i < 8; i++ ) {
		char s[ 2 ] = { ( ( b & ( 1 << i ) ) != 0 ) + '0', '\0' };
		std::string buf = s;
		str = buf + str;
	}
	return str;
};
