#include "EventTitle.h"
#include "Military.h"
#include "Office.h"
#include "Storage.h"

EventTitle::EventTitle( ) :
Event( EVENT_TITLE ) {
	Military::getTask( )->eraseEventEnemy( );
}


EventTitle::~EventTitle( ) {
}

void EventTitle::update( ) {
}

