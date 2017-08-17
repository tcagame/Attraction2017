#include "Pop.h"

const int POP_INTERVAL_COUNT = 600;

Pop::Pop( const Vector& pos ) :
_pos( pos ),
_count( POP_INTERVAL_COUNT ) {
}

Pop::~Pop( ) {
}

void Pop::update( ) {
	if ( !( _count > POP_INTERVAL_COUNT )  ) {
		if ( isInScreen( ) ) {
			//エネミーを出現させる
			create( );
			_count = 0;
		}
	}
	_count++;
}

bool Pop::isInScreen( ) const {
	bool result = true;
	return result;
}

Vector Pop::getPos( ) const {
	return _pos;
}
