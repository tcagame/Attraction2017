#include "PopEyeDaemon.h"
#include "EnemyEyeDaemon.h"
#include "Military.h"
#include "Property.h"

PopEyeDaemon::PopEyeDaemon( const Vector& pos ) :
Pop( pos ) {
	_max_pop_time = Property::getTask( )->getData( "EyeDaemon_POP_TIME" );
	_count = _max_pop_time;
}


PopEyeDaemon::~PopEyeDaemon( ) {
}

void PopEyeDaemon::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > _max_pop_time ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyEyeDaemon( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}