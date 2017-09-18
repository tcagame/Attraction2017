#include "Pop.h"
#include "ace_define.h"
#include "Family.h"
#include "World.h"
#include "Map.h"

const int POP_INTERVAL_COUNT = 600;
const int MAX_PAGE = SCREEN_WIDTH / GRAPH_SIZE;
const int POP_RANGE = SCREEN_WIDTH * 3 / 2;

Pop::Pop( const Vector& pos ) :
_pos( pos ),
_count( POP_INTERVAL_COUNT ) {
}

Pop::~Pop( ) {
}

void Pop::update( ) {
	MapPtr map = World::getTask( )->getMap( AREA_STREET );
	//posをカメラに合わせる
	double camera_pos = Family::getTask( )->getCameraPosX( );
	while ( _pos.x < camera_pos ) {
		int width = map->getPageNum( ) * GRAPH_SIZE;
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
	int enemy_page = ( ( int )_pos.x - Family::getTask( )->getCameraPosX( ) ) / GRAPH_SIZE;
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
