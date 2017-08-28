#include "RockMapBoss.h"
#include "RockMapBossDrawer.h"

const int MOVE_TO_NEXT_TIME = 300;

RockMapBoss::RockMapBoss( ) :
_time( 0 ) {
}

RockMapBoss::~RockMapBoss( ) {
}

void RockMapBoss::initialize( ) {
	_drawer = RockMapBossDrawerPtr( new RockMapBossDrawer( STAGE_FIRE ) );
}

void RockMapBoss::update( ) {
	_time++;
	if ( _time > MOVE_TO_NEXT_TIME ) {
		STAGE next = ( STAGE )( ( _drawer->getStage( ) + 2 ) % ( int )MAX_STAGE );
		_drawer.reset( );
		_drawer = RockMapBossDrawerPtr( new RockMapBossDrawer( next ) );
		_time = 0;
	}
}
