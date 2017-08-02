#include "Enemy.h"
#include "Family.h"
#include <assert.h>


Enemy::Enemy( const Vector& pos, const int width, bool mass ) :
Character( pos, width, mass ) {
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
	int screen_page_min = ( int )Family::getTask( )->getCameraPos( ) / GRAPH_SIZE;
	int screen_page_max = screen_page_min + SCREEN_WIDTH / GRAPH_SIZE;
	
	if ( enemy_page < screen_page_min ||
		 enemy_page > screen_page_max ) {
		result = false;
	}
	return result;
}
