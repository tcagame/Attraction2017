#include "EventTitle.h"
EventTitle::EventTitle( ) :
Event( EVENT_NONE, DIR_LEFT ) {
	start( true );
}


EventTitle::~EventTitle( ) {
}

void EventTitle::update( ) {
}

bool EventTitle::isJoining( ) const {
	return false;
}

void EventTitle::join( PLAYER target ) {

}