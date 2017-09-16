#include "EventTitle.h"
#include "Military.h"
#include "Office.h"
#include "Storage.h"

EventTitle::EventTitle( ) :
Event( EVENT_NONE ) {
	Military::getTask( )->eraseEventEnemy( );
}


EventTitle::~EventTitle( ) {
}

void EventTitle::update( ) {
}

bool EventTitle::isFinished( ) const {
	return false;
}

bool EventTitle::isJoining( ) const {
	return false;
}

void EventTitle::join( PLAYER target ) {

}