#include "EventBudha.h"



EventBudha::EventBudha( ) :
Event( EVENT_BUDHA, DIR_RIGHT ) {
}


EventBudha::~EventBudha( ) {
}

void EventBudha::update( ) {
}

bool EventBudha::isJoining( ) const {
	return false;
}

void EventBudha::join( PLAYER target ) {

}