#include "PopMoth.h"
#include "EnemyMoth.h"
#include "Military.h"

const int MAX_POP_COUNT = 300;
const int POP_RANGE = 100;

PopMoth::PopMoth( const Vector& pos ) :
Pop( pos ),
_count( MAX_POP_COUNT ) {
}


PopMoth::~PopMoth( ) {
}

void PopMoth::update( ) {
	//ƒvƒŒƒCƒ„[‚ª‹ß‚­‚É‚«‚½‚ç•¦‚­
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > MAX_POP_COUNT ) {
		if ( isInRangePlayer( POP_RANGE ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyMoth( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}