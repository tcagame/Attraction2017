#include "PopHugDaemon.h"
#include "EnemyHugDaemon.h"
#include "Military.h"
#include "Property.h"

PopHugDaemon::PopHugDaemon( const Vector& pos ) :
Pop( pos ) {
	_max_pop_time = Property::getTask( )->getData( "HugDaemon_POP_TIME" );
	_count = _max_pop_time;
}


PopHugDaemon::~PopHugDaemon( ) {
}

void PopHugDaemon::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > _max_pop_time ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyHugDaemon( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}