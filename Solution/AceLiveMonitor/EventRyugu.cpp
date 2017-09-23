#include "EventRyugu.h"
#include "Office.h"

EventRyugu::EventRyugu( ) :
Event( EVENT_RYUGU, DIR_RIGHT ) {
	Office::getTask( )->popUpNPC( EVENT_RYUGU );
}


EventRyugu::~EventRyugu( ) {
}

void EventRyugu::update( ) {
}

void EventRyugu::join( PLAYER target ) {

}