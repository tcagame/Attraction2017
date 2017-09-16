#include "Enemy.h"
#include "Family.h"
#include <assert.h>
#include "SynchronousData.h"

Enemy::Enemy( const Vector& pos, const int chip_size, const int hp, bool mass ) :
Character( pos, chip_size, hp, mass ),
//後に全てのエネミーのコンストラクターで指定する
_force( 3 ) {
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
	if ( getArea( ) != AREA_EVENT ) {
		add = Family::getTask( )->getCameraPosX( ) / GRAPH_SIZE;
	}
	int screen_page_min = 0 + add;
	int screen_page_max = SCREEN_WIDTH / GRAPH_SIZE + 1 + add;
	if ( enemy_page < screen_page_min ||
		 enemy_page > screen_page_max ) {
		result = false;
	}
	if ( getArea( ) == AREA_EVENT ) {
		Vector vec = getVec( );
		if ( pos.x + vec.x - getOverlappedRadius( ) < 0 ) {
			result = false;
		}
	}
	return result;
}

int Enemy::getForce( ) const {
	return _force;
}

void Enemy::setForce( int force ) {
	_force = force;
}

unsigned char Enemy::getType( ) const {
	unsigned char type = 0;
	switch ( getChipSize( ) ) {
	case SMALL_CHAR_GRAPH_SIZE:
		type = SynchronousData::TYPE_ENEMY_SMALL;
		break;
	case NORMAL_CHAR_GRAPH_SIZE:
		type = SynchronousData::TYPE_ENEMY_MIDIUM;
		break;
	case BIG_CHAR_GRAPH_SIZE:
		type = SynchronousData::TYPE_ENEMY_BIG;
		break;
	}

	return type;
}