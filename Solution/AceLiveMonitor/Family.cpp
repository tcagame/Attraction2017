#include "Family.h"
#include "Player.h"

const Vector INIT_PLAYER_POS[ ACE_PLAYER_NUM ] = {
	Vector( 10, 10 ),
	Vector( 110, 10 ),
	Vector( 210, 10 ),
	Vector( 310, 10 )
};

Family::Family( ) {
	for ( int i = 0; i < ACE_PLAYER_NUM; i++ ) {
		_player[ i ] = PlayerPtr( new Player( INIT_PLAYER_POS[ i ] ) );
	}
}


Family::~Family( ) {
}

void Family::update( ) {
	for ( int i = 0; i < ACE_PLAYER_NUM; i++ ) {
		_player[ i ]->update( );
	}
}

PlayerPtr Family::getPlayer( int player_id ) const {
	return _player[ player_id ];
}