#include "EventWood.h"
#include "Military.h"


EventWood::EventWood( ) :
Event( EVENT_WOOD ) {
	Military::getTask( )->createEventEnemy( EVENT_WOOD );
}


EventWood::~EventWood( ) {
}

void EventWood::update( ) {
}

