#include "PopFlog.h"
#include "EnemyFlog.h"
#include "Military.h"
#include "Property.h"

const int POP_RANGE = 300;

PopFlog::PopFlog( const Vector& pos ) :
Pop( pos ) {
	_max_pop_time = Property::getTask( )->getData( "Flog_POP_TIME" );
	_count = _max_pop_time;
}


PopFlog::~PopFlog( ) {
}

void PopFlog::update( ) {
	//ƒvƒŒƒCƒ„[‚ª‹ß‚­‚É‚«‚½‚ç•¦‚­
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > _max_pop_time ) {
		if ( isInRangePlayer( POP_RANGE ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyFlog( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}