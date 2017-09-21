#include "PopGhost.h"
#include "EnemyGhost.h"
#include "Military.h"
#include "Property.h"

const int POP_RANGE = 300;

PopGhost::PopGhost( const Vector& pos ) :
Pop( pos ) {
	_max_pop_time = Property::getTask( )->getData( "Ghost_POP_TIME" );
	_count = _max_pop_time;
}

PopGhost::~PopGhost( ) {
}

void PopGhost::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	//ƒvƒŒƒCƒ„[‚ª‹ß‚­‚É‚«‚½‚ç•¦‚­
	if ( _count > _max_pop_time ) {
		if ( isInRangePlayer( POP_RANGE ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyGhost( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}