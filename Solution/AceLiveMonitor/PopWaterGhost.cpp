#include "PopWaterGhost.h"
#include "EnemyWaterGhost.h"
#include "Military.h"

const int MAX_POP_COUNT = 400;
const int POP_RANGE = 200;

PopWaterGhost::PopWaterGhost( const Vector& pos ) :
Pop( pos ),
_count( MAX_POP_COUNT ) {
}


PopWaterGhost::~PopWaterGhost( ) {
}

void PopWaterGhost::update( ) {
	//ƒvƒŒƒCƒ„[‚ª‹ß‚­‚É‚«‚½‚ç•¦‚­
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > MAX_POP_COUNT ) {
		if ( isInRangePlayer( POP_RANGE ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyWaterGhost( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}