#include "RockFamily.h"
#include "Application.h"
#include "RockPlayer.h"
#include "Status.h"
#include "RockClientInfo.h"

RockFamilyPtr RockFamily::getTask( ) {
	return std::dynamic_pointer_cast< RockFamily >( Application::getInstance( )->getTask( getTag( ) ) );
}


RockFamily::RockFamily( StatusPtr status ) :
_status( status ) {
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		_player[ i ] = RockPlayerPtr( new RockPlayer( status, Vector( i * 25, 30 ), i ) );
	}
}


RockFamily::~RockFamily( ) {
}


void RockFamily::initialize( ) {
}

void RockFamily::update( ) {
	unsigned int client_id = RockClientInfo::getTask( )->getClientId( );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		Status::Player player = _status->getPlayer( i );
		if ( client_id != _status->getPlayer( i ).state ) {
			continue;
		}
		_player[ i ]->update( );
	}
}

RockPlayerPtr RockFamily::getPlayer( int id ) const {
	return _player[ id ];
}
