#include "Family.h"
#include "Player.h"
#include "Application.h"

const Vector INIT_PLAYER_POS[ ACE_PLAYER_NUM ] = {
	Vector( 50, 10 ),
	Vector( 150, 10 ),
	Vector( 250, 10 ),
	Vector( 350, 10 )
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

PlayerPtr Family::getPlayer( int player_id ) const {
	return _player[ player_id ];
}