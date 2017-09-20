#include "PopWind.h"
#include "EnemyWind.h"
#include "Military.h"

const int MAX_POP_COUNT = 400;
const int POP_RANGE = 350;

PopWind::PopWind( const Vector& pos ) :
Pop( pos ),
_count( MAX_POP_COUNT ) {
}

PopWind::~PopWind( ) {
}

void PopWind::update( ) {
	//ƒvƒŒƒCƒ„[‚ª‹ß‚­‚É‚«‚½‚ç•¦‚­
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > MAX_POP_COUNT ) {
		if ( isInRangePlayer( POP_RANGE ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyWind( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}