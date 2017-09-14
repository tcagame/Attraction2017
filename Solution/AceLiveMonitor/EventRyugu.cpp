#include "EventRyugu.h"
#include "Office.h"

EventRyugu::EventRyugu( ) :
Event( EVENT_RYUGU ) {
	Office::getTask( )->popUpNPC( EVENT_RYUGU );
}


EventRyugu::~EventRyugu( ) {
}

void EventRyugu::update( ) {
}
