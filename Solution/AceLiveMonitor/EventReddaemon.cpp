#include "EventReddaemon.h"
#include "Military.h"


EventReddaemon::EventReddaemon( ) :
Event( EVENT_REDDAEMON ) {
	Military::getTask( )->createEventEnemy( );
}


EventReddaemon::~EventReddaemon( ) {
}

void EventReddaemon::update( ) {
}