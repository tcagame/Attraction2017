#include "RockFamily.h"
#include "Application.h"
#include "RockPlayer.h"
#include "RockClientInfo.h"
#include "RockAncestors.h"
#include "RockBubble.h"
#include <assert.h>

RockFamilyPtr RockFamily::getTask( ) {
	return std::dynamic_pointer_cast< RockFamily >( Application::getInstance( )->getTask( getTag( ) ) );
}


RockFamily::RockFamily( StatusPtr status, const Vector& base_pos ) {
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		_ancestors[ i ]	= RockAncestorsPtr( new RockAncestors( i ) );
		_bubble[ i ]	= RockBubblePtr( new RockBubble( i ) );
		_player[ i ]	= RockPlayerPtr   ( new RockPlayer   ( status, Vector( i * 42, 1 ) + base_pos, i, _ancestors[ i ] ) );
	}
}


RockFamily::~RockFamily( ) {
}

void RockFamily::initialize( ) {
}

void RockFamily::update( ) {
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		if ( !_player[ i ]->isActive( ) ) {
			continue;
		}
		//player
		_player[ i ]->update( );
		for ( int j = 0; j < ROCK_PLAYER_NUM; j++ ) {
			if ( i == j ) {
				continue;
			}
			if ( _player[ j ]->isActive( ) ) {
				if ( _player[ i ]->isOverLapped( _player[ j ] ) ) {
					if ( _player[ i ]->isOnHead( _player[ j ] ) ) {
						_player[ i ]->bound( );
					} else {
						_player[ i ]->back( );
					}
				}
			}
		}
		//ancestor
		_ancestors[ i ]->update( );
		//bubble
		_bubble[ i ]->update( );
	}
}

RockPlayerPtr RockFamily::getPlayer( int id ) const {
	assert( 0 <= id && id < ROCK_PLAYER_NUM );
	return _player[ id ];
}

RockBubblePtr RockFamily::getBubble( int id ) const {
	assert( 0 <= id && id < ROCK_PLAYER_NUM );
	return _bubble[ id ];
}

RockAncestorsPtr RockFamily::getAncestors( int id ) const {
	assert( 0 <= id && id < ROCK_PLAYER_NUM );
	return _ancestors[ id ];
}

Vector RockFamily::getCameraPos( ) const {
	Vector result = Vector( );
	int num = 0;
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		if ( _player[ i ]->isActive( ) ) {
			result += _player[ i ]->getPos( );
			num++;
		}
	}
	if ( num > 0 ) {
		result *= ( 1.0 / ( double )num );
	}
	return result;
}

void RockFamily::resetPos( const Vector& base_pos ) {
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		if ( !_player[ i ]->isActive( ) ) {
			continue;
		}
		_player[ i ]->resetPos( Vector( i * 35, 1 ) + base_pos );
	}	
}
