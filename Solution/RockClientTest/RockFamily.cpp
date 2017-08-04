#include "RockFamily.h"
#include "Application.h"
#include "RockPlayer.h"
#include "Status.h"

RockFamilyPtr RockFamily::getTask( ) {
	return std::dynamic_pointer_cast< RockFamily >( Application::getInstance( )->getTask( getTag( ) ) );
}


RockFamily::RockFamily( StatusPtr status ) {
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		_player[ i ] = RockPlayerPtr( new RockPlayer( status, Vector( i * 25, 0 ), i ) );
	}
}


RockFamily::~RockFamily( ) {
}


void RockFamily::initialize( ) {
}

void RockFamily::update( ) {
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		_player[ i ]->update( );
	}
}

RockPlayerPtr RockFamily::getPlayer( int id ) const {
	return _player[ id ];
}
