#include "RockFamily.h"
#include "Application.h"
#include "RockPlayer.h"
#include "RockClientInfo.h"
#include "RockAncestors.h"
#include "RockBubble.h"
#include "RockArmoury.h"
#include "RockMilitary.h"
#include "RockEnemy.h"
#include "Sound.h"
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
			if ( _before_active[ i ] ) {
				Sound::getTask( )->stopAllSE( );
				_player[ i ]->stopEffect( );
			}
			_player[ i ]->resetPos( Vector( i * 50, 60 ) + getBeforeCameraPos( ) );
			_player[ i ]->resetBubble( );
			_before_active[ i ] = false;
			continue;
		}
		if ( !_before_active[ i ] ) {
			_player[ i ]->setAdmissionPos( getBeforeCameraPos( ) );
		}
		_before_active[ i ] = true;
		_player[ i ]->update( );

		if ( _player[ i ]->isBubble( ) ) {
			continue;
		}

		//player-player
		RockPlayerPtr overlapped_player = getOverLappedPlayer( _player[ i ] );
		if ( overlapped_player ) {
			if ( _player[ i ]->isOnHead( overlapped_player ) ) {
				_player[ i ]->bound( );
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
				_player[ i ]->knockBack( overlapped_enemy );
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
			result += _player[ i ]->getPos( ) * 0.01;
			num++;
		}
	}
	if ( num > 0 ) {
		result *= ( 1.0 / ( double )num );
	}
	result *= 100;
	return result;
}

void RockFamily::resetPos( const Vector& base_pos ) {
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		if ( _player[ i ]->isActive( ) ) {
			_player[ i ]->resetPos( Vector( i * 35, 1 ) + base_pos );
		}
		if ( _ancestors[ i ]->isActive( ) ) {
			_ancestors[ i ]->resetPos( );
		}
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

Vector RockFamily::getBeforeCameraPos( ) const {
	Vector result = Vector( );
	int num = 0;
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		if ( _before_active[ i ] ) {
			result += _player[ i ]->getPos( ) * 0.01;
			num++;
		}
	}
	if ( num > 0 ) {
		result *= ( 1.0 / ( double )num );
		result *= 100;
	} else {
		result = _base_pos;
	}

	result += Vector( 75, 0 );
	return result;
}
