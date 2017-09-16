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

