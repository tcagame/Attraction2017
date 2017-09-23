#include "EventLake.h"



EventLake::EventLake( ) :
Event( EVENT_LAKE, DIR_RIGHT ) {
}


EventLake::~EventLake( ) {
}

void EventLake::update( ) {
}


bool EventLake::isFinished( ) const {
	return true;
}

void EventLake::join( PLAYER target ) {

}