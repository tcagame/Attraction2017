#include "EventWood.h"
#include "Military.h"
#include "EnemyBossMonsterTree.h"

EventWood::EventWood( ) :
Event( EVENT_WOOD ) {
	_boss = EnemyBossPtr( new EnemyBossMonsterTree( Vector( 800, 225 ) ) );
	Military::getTask( )->popUp( _boss );
}


EventWood::~EventWood( ) {
}

void EventWood::update( ) {
}

bool EventWood::isFinished( ) const {
	return true;
}

bool EventWood::isJoining( ) const {
	return false;
}

void EventWood::join( PLAYER target ) {

}