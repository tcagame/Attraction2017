#include "Enemy.h"
#include "Family.h"
#include <assert.h>


Enemy::Enemy( const Vector& pos, const int chip_size, const int hp, bool mass ) :
Character( pos, chip_size, mass ) {
	setDir( DIR_LEFT );
}


Enemy::~Enemy( ) {
}

bool Enemy::isInScreen( ) const {
	Vector pos = getPos( );
	assert( pos.y < GRAPH_SIZE );
	bool result = true;
	//エネミーの位置
	int enemy_page = ( int )getPos( ).x / GRAPH_SIZE;
	//スクリーンの端
	int add = 0;
	if ( getState( ) != STATE_EVENT ) {
		add = ( int )Family::getTask( )->getCameraPos( ) / GRAPH_SIZE;
	}
	int screen_page_min = 0 + add;
	int screen_page_max = SCREEN_WIDTH / GRAPH_SIZE + 1 + add;
	if ( enemy_page < screen_page_min ||
		 enemy_page > screen_page_max ) {
		result = false;
	}
	if ( getState( ) == STATE_EVENT ) {
		Vector vec = getVec( );
		if ( pos.x + vec.x - getRadius( ) < 0 ) {
			result = false;
		}
	}
	return result;
}
