#include "EventFlame.h"
#include "Military.h"


EventFlame::EventFlame( ) :
Event( EVENT_FLAME ) {
	Military::getTask( )->createEventEnemy( EVENT_FLAME );
}


EventFlame::~EventFlame( ) {
}

void EventFlame::update( ) {
}
