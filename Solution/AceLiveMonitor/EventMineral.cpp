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


bool EventMineral::isFinished( ) const {
	return true;
}

bool EventMineral::isJoining( ) const {
	return false;
}

void EventMineral::join( PLAYER target ) {

}