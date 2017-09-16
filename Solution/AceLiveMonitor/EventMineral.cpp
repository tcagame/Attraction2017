#include "EventMineral.h"
#include "Military.h"
#include "EnemyBossRock.h"

EventMineral::EventMineral( ) :
Event( EVENT_MINERAL ) {
	_boss = EnemyBossPtr( new EnemyBossRock( Vector( 800, 225 ) ) );
	Military::getTask( )->popUp( _boss );
}


EventMineral::~EventMineral( ) {
}

void EventMineral::update( ) {
}
