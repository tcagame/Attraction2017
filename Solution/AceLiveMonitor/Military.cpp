#include "Military.h"
#include "Application.h"
#include "ace_define.h"
#include "Family.h"
#include "Player.h"
#include "EnemyBossRedDemon.h"
#include "EnemyBossBloodDemon.h"
#include "EnemyBossMonsteTreer.h"
#include "EnemyBossRock.h"
#include "MapEvent.h"
#include "Impact.h"

PTR( Player );

MilitaryPtr Military::getTask( ) {
	return std::dynamic_pointer_cast< Military >( Application::getInstance( )->getTask( getTag( ) ) );
}


Military::Military( ) {
}


Military::~Military( ) {
}

void Military::update( ) {
	{//main
		std::list< EnemyPtr >::const_iterator ite = _enemies.begin( );
		while ( ite != _enemies.end( ) ) {
			EnemyPtr enemy = (*ite);
			if ( !enemy ) {
				ite++;
				continue;
			}
			if ( enemy->isFinished( ) ||
				 !enemy->isInScreen( ) ) {
				int chip_size = enemy->getChipSize( ) * 2;
				_impacts.push_back( ImpactPtr( new Impact( enemy->getPos( ), Character::STATE_MAIN, chip_size ) ) );
				ite = _enemies.erase( ite );
				continue;
			}
			FamilyPtr family( Family::getTask( ) );
			for ( int i = 0; i < ACE_PLAYER_NUM; i++ ) {
				PlayerPtr player( family->getPlayer( i ) );
				if ( player->isOverlapped( enemy ) ) {
					if ( player->isOnHead( enemy ) ) {
						player->bound( );
					} else {
						player->damage( 1 );
					}
				}
			}
			enemy->update( );
			ite++;
		}
	}
	{//event
		if ( _boss ) {
			_boss->update( );
			if ( _boss->isFinished( ) ) {
				_boss = EnemyPtr( );
			}
		}
		std::list< EnemyPtr >::const_iterator ite = _event_enemies.begin( );
		while ( ite != _event_enemies.end( ) ) {
			EnemyPtr enemy = (*ite);
			if ( !enemy ) {
				ite++;
				continue;
			}
			if ( enemy->isFinished( ) ||
				 !enemy->isInScreen( ) ) {
				int chip_size = enemy->getChipSize( ) * 2;
				_impacts.push_back( ImpactPtr( new Impact( enemy->getPos( ), Character::STATE_EVENT, chip_size ) ) );
				ite = _event_enemies.erase( ite );
				continue;
			}
			FamilyPtr family( Family::getTask( ) );
			for ( int i = 0; i < ACE_PLAYER_NUM; i++ ) {
				PlayerPtr player( family->getPlayer( i ) );
				if ( player->isOverlapped( enemy ) ) {
					if ( player->isOnHead( enemy ) ) {
						player->bound( );
					} else {
						player->damage( 1 );
					}
				}
			}
			enemy->update( );
			ite++;
		}
	}

	updateImpact( );
}

const std::list< EnemyPtr > Military::getEnemyList( ) const {
	return _enemies;
}

const std::list< EnemyPtr > Military::getEventEnemyList( ) const {
	return _event_enemies;
}


void Military::popUp( EnemyPtr enemy ) {
	_enemies.push_back( enemy );
}

void Military::popUpEventEnemy( EnemyPtr enemy ) {
	_event_enemies.push_back( enemy );
}

EnemyPtr Military::getOverLappedEnemy( CharacterConstPtr character ) const {
	EnemyPtr result = EnemyPtr( );
	if ( character->getState( ) == Character::STATE_MAIN ) {
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
	} else {
		if ( _boss ) {
			if ( _boss->isOverlapped( character ) ) {
				result = _boss;
			}
		}
		std::list< EnemyPtr >::const_iterator ite = _event_enemies.begin( );
		while ( ite != _event_enemies.end( ) ) {
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
	}
	return result;
}

void Military::createBoss( ) {
	ViewerEvent::TYPE type = MapEvent::getTask( )->getType( );
	_event_enemies = { };
	switch ( type ) {
	case ViewerEvent::TYPE_TITLE:
		_boss = EnemyPtr( );
		break;
	case ViewerEvent::TYPE_RED_DEMON:
		_boss = EnemyPtr( new EnemyBossRedDemon( Vector( 800, 200 ) ) );
		break;
	case ViewerEvent::TYPE_FIRE:
		_boss = EnemyPtr( new EnemyBossBloodDemon( Vector( 800, 200 ) ) );
		break;
	case ViewerEvent::TYPE_TREE:
		_boss = EnemyPtr( new EnemyBossMonsteTreer( Vector( 800, 225 ) ) );
		break;
	case ViewerEvent::TYPE_ROCK:
		_boss = EnemyPtr( new EnemyBossRock( Vector( 800, 225 ) ) );
		break;
	//case ViewerEvent::TYPE_SHOP:
	//	_boss = EnemyPtr( new EnemyBossRock( Vector( 800, 225 ) ) );
	//	break;
	}
}

EnemyPtr Military::getBoss( ) const {
	return _boss;
}

void Military::updateImpact( ) {
	std::list< ImpactPtr >::iterator ite = _impacts.begin( );
	while( ite != _impacts.end( ) ) {
		if ( !( *ite ) ) {
			ite++;
			continue;
		}

		ImpactPtr impact = *ite;
		if ( impact->isFinished( ) ) {
			ite = _impacts.erase( ite );
			continue;
		}
		impact->update( );
		ite++;
	}
}

std::list< ImpactPtr > Military::getImpactList( ) const {
	return _impacts;
}