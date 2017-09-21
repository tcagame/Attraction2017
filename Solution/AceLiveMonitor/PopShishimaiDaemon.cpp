#include "PopShishimaiDaemon.h"
#include "EnemyShishimaiDaemon.h"
#include "Military.h"
#include "Property.h"

PopShishimaiDaemon::PopShishimaiDaemon( const Vector& pos ) :
Pop( pos ) {
	_max_pop_time = Property::getTask( )->getData( "ShishimaiDaemon_POP_TIME" );
	_count = _max_pop_time;
}


PopShishimaiDaemon::~PopShishimaiDaemon( ) {
}

void PopShishimaiDaemon::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > _max_pop_time ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyShishimaiDaemon( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}