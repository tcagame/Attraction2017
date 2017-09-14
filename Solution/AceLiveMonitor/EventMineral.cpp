#include "EventMineral.h"
#include "Military.h"


EventMineral::EventMineral( ) :
Event( EVENT_MINERAL ) {
	Military::getTask( )->createEventEnemy( );
}


EventMineral::~EventMineral( ) {
}

void EventMineral::update( ) {
}
