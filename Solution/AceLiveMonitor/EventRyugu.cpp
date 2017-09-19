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


bool EventRyugu::isFinished( ) const {
	return true;
}

bool EventRyugu::isJoining( ) const {
	return false;
}

void EventRyugu::join( PLAYER target ) {

}