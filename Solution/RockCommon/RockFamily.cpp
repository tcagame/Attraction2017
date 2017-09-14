#include "RockFamily.h"
#include "Application.h"
#include "RockPlayer.h"
#include "RockClientInfo.h"
#include "RockAncestors.h"
#include "RockBubble.h"
#include "RockArmoury.h"
#include "RockMilitary.h"
#include "RockEnemy.h"
#include <assert.h>

RockFamilyPtr RockFamily::getTask( ) {
	return std::dynamic_pointer_cast< RockFamily >( Application::getInstance( )->getTask( getTag( ) ) );
}


RockFamily::RockFamily( StatusPtr status, const Vector& base_pos ) :
_base_pos( base_pos ) {
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		_ancestors[ i ]	= RockAncestorsPtr( new RockAncestors( i ) );
		_bubble[ i ]	= RockBubblePtr( new RockBubble( i ) );
		_player[ i ]	= RockPlayerPtr( new RockPlayer( status, Vector( i * 50, 75 ) + base_pos, i, _ancestors[ i ] ) );
	}
}


RockFamily::~RockFamily( ) {
}

void RockFamily::initialize( ) {
}

void RockFamily::update( ) {
	updatePlayer( );
	updateBubble( );
	updateAncestors( );
}

void RockFamily::updatePlayer( ) {
	RockMilitaryPtr military( RockMilitary::getTask( ) );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		if ( !_player[ i ]->isActive( ) ) {
			//_player[ i ]->resetPos( Vector( i * 50, 75 ) + _base_pos );
			//_player[ i ]->resetBubble( );
			continue;
		}
		_player[ i ]->update( );

		//player-player
		RockPlayerPtr overlapped_player = getOverLappedPlayer( _player[ i ] );
		if ( overlapped_player ) {
			if ( _player[ i ]->isOnHead( overlapped_player ) ) {
				_player[ i ]->bound( );
			} else {
				_player[ i ]->adjustPosForOverLapped( overlapped_player );
			}
		}
		//player_enemy
		RockEnemyPtr overlapped_enemy = military->getOverLappedEnemy( _player[ i ] );
		if ( overlapped_enemy ) {
			if ( _player[ i ]->isOnHead( overlapped_enemy ) ) {
				_player[ i ]->bound( );
			} else {
				int force = -overlapped_enemy->getForce( );
				_player[ i ]->damage( force );
				_player[ i ]->adjustPosForOverLapped( overlapped_enemy );
			}
		}
	}
}
void RockFamily::updateAncestors( ) {
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		if ( _ancestors[ i ]->isActive( ) ) {
			_ancestors[ i ]->update( );
		}
	}
}
void RockFamily::updateBubble( ) {
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		//Bubble‚ÍactiveŠÖŒW‚È‚µ‚Éí‚Éupdate
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
	RockArmoury::getTask( )->clearShot( );
}


RockPlayerPtr RockFamily::getOverLappedPlayer( RockCharacterPtr target ) const {
	RockPlayerPtr result = RockPlayerPtr( );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		if ( target == _player[ i ] ) {
			continue;
		}
		if ( !_player[ i ]->isActive( ) ) {
			continue;
		}
		if ( _player[ i ]->isOverLapped( target ) ) {
			result = _player[ i ];
			break;
		}
	}
	return result;
}