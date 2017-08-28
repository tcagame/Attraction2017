#include "RockMapStreet.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockMapStreetDrawer.h"

const int REMOVE_CAVE_TIME = 300;

RockMapStreet::RockMapStreet( ) :
_time( 0 ) {
}

RockMapStreet::~RockMapStreet( ) {
}

void RockMapStreet::initialize( ) {
	_drawer = RockMapStreetDrawerPtr( new RockMapStreetDrawer( STAGE_STREET ) );
}

void RockMapStreet::update( ) {
	switch ( _drawer->getStage( ) ) {
	case STAGE_STREET:
		updateStreet( );
		break;
	case STAGE_CAVE:
		updateCave( );
		break;
	}
}

void RockMapStreet::updateStreet( ) {
	RockFamilyPtr family = RockFamily::getTask( );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		RockPlayerPtr player = family->getPlayer( i );
		if ( !player->isActive( ) ) {
			continue;
		}

		double length = ( Vector( -200, 0, -500 ) - player->getPos( ) ).getLength( );
		if ( length < 100 ) {
			_drawer.reset( );
			_drawer = RockMapStreetDrawerPtr( new RockMapStreetDrawer( STAGE_CAVE ) );
			family->resetPos( Vector( 0, 10, 0 ) );
		}
	}
}

void RockMapStreet::updateCave( ) {
	_time++;
	RockFamilyPtr family = RockFamily::getTask( );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		RockPlayerPtr player = family->getPlayer( i );
		if ( !player->isActive( ) ) {
			continue;
		}

		if ( _time > REMOVE_CAVE_TIME ) {
			_drawer.reset( );
			_drawer = RockMapStreetDrawerPtr( new RockMapStreetDrawer( STAGE_STREET ) );
			family->resetPos( Vector( 0, 30, -500 ) );
			_time = 0;
		}
	}
}
