#include "PopBat.h"
#include "EnemyBat.h"
#include "Military.h"

const int MAX_POP_COUNT = 300;
const int POP_RANGE = 100;

PopBat::PopBat( const Vector& pos ) :
Pop( pos ),
_count( MAX_POP_COUNT ) {
}


PopBat::~PopBat( ) {
}

void PopBat::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	//プレイヤーが近くにきたら沸く
	if ( _count > MAX_POP_COUNT ) {
		if ( isInRangePlayer( POP_RANGE ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyBat( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_count = 0;
			_enemy = enemy;
		}
	}
	_count++;
}