#include "Military.h"
#include "Application.h"
#include "ace_define.h"
#include "Family.h"
#include "Player.h"
#include "EnemyBossRedDemon.h"
#include "MapEvent.h"

PTR( Player );

MilitaryPtr Military::getTask( ) {
	return std::dynamic_pointer_cast< Military >( Application::getInstance( )->getTask( getTag( ) ) );
}


Military::Military( ) {
}


Military::~Military( ) {
}

void Military::update( ) {
	std::list< EnemyPtr >::const_iterator ite = _enemies.begin( );
	while ( ite != _enemies.end( ) ) {
		EnemyPtr enemy = (*ite);
		if ( !enemy ) {
			ite++;
			continue;
		}
		if ( enemy->isFinished( ) ||
			 !enemy->isInScreen( ) ) {
			ite = _enemies.erase( ite );
			continue;
		}
		FamilyPtr family( Family::getTask( ) );
		for ( int i = 0; i < ACE_PLAYER_NUM; i++ ) {
			PlayerPtr player( family->getPlayer( i ) );
			if ( player->isOverlapped( enemy ) ) {
				player->damage( 1 );
			}
		}
		enemy->update( );
		ite++;
	}
	if ( _boss ) {
		_boss->update( );
	}
}

const std::list< EnemyPtr > Military::getList( ) const {
	return _enemies;
}

void Military::popUp( EnemyPtr enemy ) {
	_enemies.push_back( enemy );
}

EnemyPtr Military::getOverLappedEnemy( CharacterConstPtr character ) const {
	EnemyPtr result = EnemyPtr( );
	std::list< EnemyPtr >::const_iterator ite = _enemies.begin( );
	while ( ite != _enemies.end( ) ) {
		EnemyPtr enemy = (*ite);
		if ( !enemy ) {
			ite++;
			continue;
		}
		if ( enemy->isOverlapped( character ) ) {
			result = enemy;
			break;
		}
		ite++;
	}
	if ( _boss ) {
		_boss->isOverlapped( character );
	}
	return result;
}

void Military::createBoss( ) {
	ViewerEvent::TYPE type = MapEvent::getTask( )->getType( );
	switch ( type ) {
	case ViewerEvent::TYPE_TITLE:
		_boss = EnemyPtr( );
		break;
	case ViewerEvent::TYPE_RED_DEMON:
		_boss = EnemyPtr( new EnemyBossRedDemon( Vector( 800, 200 ) ) );
		break;
	}
}

EnemyPtr Military::getBoss( ) const {
	return _boss;
}
