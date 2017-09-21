#include "PopMoth.h"
#include "EnemyMoth.h"
#include "Military.h"
#include "Property.h"

const int POP_RANGE = 200;

PopMoth::PopMoth( const Vector& pos ) :
Pop( pos ) {
	_max_pop_time = Property::getTask( )->getData( "Moth_POP_TIME" );
	_count = _max_pop_time;
}


PopMoth::~PopMoth( ) {
}

void PopMoth::update( ) {
	//ƒvƒŒƒCƒ„[‚ª‹ß‚­‚É‚«‚½‚ç•¦‚­
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > _max_pop_time ) {
		if ( isInRangePlayer( POP_RANGE ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyMoth( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}