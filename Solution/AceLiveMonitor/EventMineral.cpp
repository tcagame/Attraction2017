#include "EventMineral.h"
#include "Military.h"


EventMineral::EventMineral( ) :
Event( EVENT_MINERAL ) {
	Military::getTask( )->createEventEnemy( EVENT_MINERAL );
}


EventMineral::~EventMineral( ) {
}

void EventMineral::update( ) {
}
