#include "EventGamble.h"



EventGamble::EventGamble( ) :
Event( EVENT_GAMBLE ) {
}


EventGamble::~EventGamble( ) {
}

void EventGamble::update( ) {
}


bool EventGamble::isFinished( ) const {
	return true;
}

bool EventGamble::isJoining( ) const {
	return false;
}

void EventGamble::join( PLAYER target ) {

}