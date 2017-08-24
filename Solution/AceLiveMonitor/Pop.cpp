#include "Pop.h"
#include "ace_define.h"
#include "Family.h"
#include "MapStreet.h"

static const int POP_INTERVAL_COUNT = 600;
static const int MAX_PAGE = SCREEN_WIDTH / GRAPH_SIZE;
static const int POP_RANGE = SCREEN_WIDTH * 3 / 2;

Pop::Pop( const Vector& pos ) :
_pos( pos ),
_count( POP_INTERVAL_COUNT ) {
}

Pop::~Pop( ) {
}

void Pop::update( ) {
	//posをカメラに合わせる
	double camera_pos = Family::getTask( )->getCameraPos( );
	while ( _pos.x < camera_pos ) {
		int width = MapStreet::getTask( )->getPageNum( ) * GRAPH_SIZE;
		_pos.x += width;
	}

	//エネミーを出現させる
	if ( _count > POP_INTERVAL_COUNT ) {
		if ( isInScreen( ) ) {
			create( );
			_count = 0;
		}
	}
	if ( camera_pos < _pos.x &&
		 _pos.x < camera_pos + POP_RANGE ) {
		_count++;
	}
}

bool Pop::isInScreen( ) const {
	bool result = true;
	//エネミーの位置
	int enemy_page = ( ( int )_pos.x - ( int )Family::getTask( )->getCameraPos( ) ) / GRAPH_SIZE;
	//エネミーが画面外にいるかどうか
	if ( enemy_page < 0 ||
		 enemy_page > MAX_PAGE ) {
		result = false;
	}
	return result;
}

Vector Pop::getPos( ) const {
	return _pos;
}
