#include "RockFamily.h"
#include "Application.h"
#include "RockPlayer.h"
#include "Status.h"
#include "RockClientInfo.h"
#include <assert.h>

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
	assert( 0 <= id && id < ROCK_PLAYER_NUM );
	return _player[ id ];
}

Vector RockFamily::getCameraPos( unsigned int state ) const {
	Vector result = Vector( );
	int i = 0;
	for ( i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		if ( _status->getPlayer( i ).state == state ) {
			result += _player[ i ]->getPos( );
		}
	}
	result *= ( 1.0 / ( double )i );

	return result;
}