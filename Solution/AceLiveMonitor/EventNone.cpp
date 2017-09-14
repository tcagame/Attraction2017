#include "EventNone.h"
#include "Military.h"
#include "Office.h"
#include "Storage.h"

EventNone::EventNone( ) :
Event( EVENT_NONE ) {
	Storage::getTask( )->eraseEventItem( );
	Office::getTask( )->eraseNPC( );
	Military::getTask( )->eraseEventEnemy( );
}


EventNone::~EventNone( ) {
}

void EventNone::update( ) {
}

