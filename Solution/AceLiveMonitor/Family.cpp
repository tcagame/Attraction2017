#include "Family.h"
#include "Player.h"
#include <assert.h>

const Vector INIT_PLAYER_POS[ ACE_PLAYER_NUM ] = {
	Vector( 50, 10 ),
	Vector( 150, 10 ),
	Vector( 250, 10 ),
	Vector( 350, 10 )
};

Family::Family( ) {
	for ( int i = 0; i < ACE_PLAYER_NUM; i++ ) {
		_player[ i ] = PlayerPtr( new Player( i, INIT_PLAYER_POS[ i ] ) );
	}
}


Family::~Family( ) {
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