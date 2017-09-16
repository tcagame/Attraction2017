#include "EventFlame.h"
#include "Military.h"
#include "EnemyBossBloodDaemon.h"

EventFlame::EventFlame( ) :
Event( EVENT_FLAME ) {
	_boss = EnemyBossPtr( new EnemyBossBloodDaemon( Vector( 800, 200 ) ) );
	Military::getTask( )->popUp( _boss );
}


EventFlame::~EventFlame( ) {
}

void EventFlame::update( ) {
}
