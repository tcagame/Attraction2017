#include "EventGamble.h"



EventGamble::EventGamble( ) :
Event( EVENT_GAMBLE, DIR_LEFT ) {
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