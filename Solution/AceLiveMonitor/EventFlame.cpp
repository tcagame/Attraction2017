#include "EventFlame.h"
#include "Military.h"


EventFlame::EventFlame( ) :
Event( EVENT_FLAME ) {
	Military::getTask( )->createEventEnemy( );
}


EventFlame::~EventFlame( ) {
}

void EventFlame::update( ) {
}
