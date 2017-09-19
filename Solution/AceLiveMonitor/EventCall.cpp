#include "EventCall.h"


EventCall::EventCall( ) :
Event( EVENT_CALL, DIR_LEFT ) {
}


EventCall::~EventCall( ) {
}

void EventCall::update( ) {
}

bool EventCall::isFinished( ) const {
	return true;
}

bool EventCall::isJoining( ) const {
	return false;
}

void EventCall::join( PLAYER target ) {

}