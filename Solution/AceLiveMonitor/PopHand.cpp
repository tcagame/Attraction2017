#include "PopHand.h"
#include "EnemyHand.h"
#include "Military.h"

const int MAX_POP_COUNT = 1000;
const int POP_RANGE = 250;

PopHand::PopHand( const Vector& pos ) :
Pop( pos ),
_count( MAX_POP_COUNT ) {
}


PopHand::~PopHand( ) {
}

void PopHand::update( ) {
	//プレイヤーが近くにきたら沸く
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > MAX_POP_COUNT ) {
		if ( isInRangePlayer( POP_RANGE ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyHand( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}