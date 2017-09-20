#include "PopNoFace.h"
#include "EnemyNoFace.h"
#include "Military.h"

const int MAX_POP_COUNT = 400;
const int POP_RANGE = 400;

PopNoFace::PopNoFace( const Vector& pos ) :
Pop( pos ),
_count( MAX_POP_COUNT ) {
}

PopNoFace::~PopNoFace( ) {
}

void PopNoFace::update( ) {
	//プレイヤーが近くにきたら沸く
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > MAX_POP_COUNT ) {
		if ( isInRangePlayer( POP_RANGE ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyNoFace( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}