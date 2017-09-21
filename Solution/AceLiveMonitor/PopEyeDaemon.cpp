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
	if ( _count > _max_pop_time ) {
		if ( isInScreen( ) ) {
			Military::getTask( )->popUp( EnemyPtr( new EnemyEyeDaemon( getPos( ) ) ) );
			_count = 0;
		}
	}
	_count++;
}