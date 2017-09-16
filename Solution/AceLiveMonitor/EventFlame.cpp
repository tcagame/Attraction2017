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

bool EventFlame::isFinished( ) const {
	return true;
}

bool EventFlame::isJoining( ) const {
	return false;
}

void EventFlame::join( PLAYER target ) {

}