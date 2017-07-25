#include "Family.h"
#include "Player.h"
#include "Application.h"
#include <assert.h>

const Vector INIT_PLAYER_POS[ ACE_PLAYER_NUM ] = {
	Vector( 250, 10 ),
	Vector( 350, 10 ),
	Vector( 450, 10 ),
	Vector( 550, 10 )
};

FamilyPtr Family::getTask( ) {
	return std::dynamic_pointer_cast< Family >( Application::getInstance( )->getTask( getTag( ) ) );
}


Family::Family( ) {
}


Family::~Family( ) {
}

void Family::initialize( ) {
	for ( int i = 0; i < ACE_PLAYER_NUM; i++ ) {
		_player[ i ] = PlayerPtr( new Player( i, INIT_PLAYER_POS[ i ] ) );
	}
}

void Family::update( ) {
	for ( int i = 0; i < ACE_PLAYER_NUM; i++ ) {
		_player[ i ]->update( );
	}
}

PlayerConstPtr Family::getPlayer( int player_id ) const {
	assert( player_id < ACE_PLAYER_NUM );
	assert( player_id >= 0 );
	return _player[ player_id ];
}

PlayerPtr Family::getPlayer( int player_id ) {
	assert( player_id < ACE_PLAYER_NUM );
	assert( player_id >= 0 );
	return _player[ player_id ];
}

double Family::getPlayersPosX( ) const {
	return ( ( _player[ 0 ]->getPos( ).x + _player[ 1 ]->getPos( ).x + _player[ 2 ]->getPos( ).x + _player[ 3 ]->getPos( ).x ) * 0.25 );
}