#include "Military.h"
#include "Application.h"
#include "ace_define.h"
#include "Family.h"
#include "Player.h"
#include "EnemyBossRedDemon.h"
#include "EnemyBossBloodDemon.h"
#include "EnemyBossMonsteTree.h"
#include "EnemyBossRock.h"
#include "MapEvent.h"
#include "Impact.h"
#include "Storage.h"
#include "ItemMoney.h"
#include "EnemyBat.h"

PTR( Player );

MilitaryPtr Military::getTask( ) {
	return std::dynamic_pointer_cast< Military >( Application::getInstance( )->getTask( getTag( ) ) );
}


Military::Military( ) {
}


Military::~Military( ) {
}

void Military::update( ) {
	FamilyPtr family( Family::getTask( ) );
	StoragePtr storage( Storage::getTask( ) );
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
				//エネミーが倒れた場合、倒れた位置で爆発する
				dropMoney( enemy );
				int chip_size = enemy->getChipSize( );
				_impacts.push_back( ImpactPtr( new Impact( enemy->getPos( ) + Vector( 0, enemy->getChipSize( ) / 2 ), Character::STATE_MAIN, chip_size * 2 ) ) );
				ite = _enemies.erase( ite );
				continue;
			}
			for ( int i = 0; i < ACE_PLAYER_NUM; i++ ) {
				PlayerPtr player( family->getPlayer( i ) );
				if ( player->isOverlapped( enemy ) ) {
					if ( player->isOnHead( enemy ) ) {
						player->bound( );
					} else {
						player->damage( 3 );
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
			for ( int i = 0; i < ACE_PLAYER_NUM; i++ ) {
				PlayerPtr player( family->getPlayer( i ) );
				if ( player->isOverlapped( _boss ) ) {
					if ( player->isOnHead( _boss ) ) {
						player->bound( );
					} else {
						player->damage( 3 );
					}
				}
			}
			if ( _boss->isFinished( ) ) {
				int impact_chip_size = _boss->getChipSize( ) * 2;
				_impacts.push_back( ImpactPtr( new Impact( _boss->getPos( ) + Vector( 0, _boss->getChipSize( ) / 2 ), Character::STATE_EVENT, impact_chip_size ) ) );
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
				//エネミーが倒れた場合、倒れた位置で爆発する
				dropMoney( enemy );
				int impact_chip_size = enemy->getChipSize( ) * 2;
				_impacts.push_back( ImpactPtr( new Impact( enemy->getPos( ) + Vector( 0, enemy->getChipSize( ) / 2 ), Character::STATE_EVENT, impact_chip_size ) ) );
				ite = _event_enemies.erase( ite );
				continue;
			}
			for ( int i = 0; i < ACE_PLAYER_NUM; i++ ) {
				PlayerPtr player( family->getPlayer( i ) );
				if ( player->isOverlapped( enemy ) ) {
					if ( player->isOnHead( enemy ) ) {
						player->bound( );
					} else {
						player->damage( 3 );
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

EnemyPtr Military::getOverlappedEnemy( CharacterConstPtr character ) const {
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
	MapEvent::TYPE type = MapEvent::getTask( )->getType( );
	_event_enemies.clear( );
	switch ( type ) {
	case MapEvent::TYPE_TITLE:
		_boss = EnemyPtr( );
		break;
	case MapEvent::TYPE_RED_DEMON:
		_boss = EnemyPtr( new EnemyBossRedDemon( Vector( 800, 200 ) ) );
		break;
	case MapEvent::TYPE_FIRE:
		_boss = EnemyPtr( new EnemyBossBloodDemon( Vector( 800, 200 ) ) );
		break;
	case MapEvent::TYPE_TREE:
		_boss = EnemyPtr( new EnemyBossMonsteTree( Vector( 800, 225 ) ) );
		break;
	case MapEvent::TYPE_ROCK:
		_boss = EnemyPtr( new EnemyBossRock( Vector( 800, 225 ) ) );
		break;
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

void Military::dropMoney( EnemyConstPtr enemy ) {
	int chip_size = enemy->getChipSize( );
	ItemMoney::TYPE type = ItemMoney::TYPE_500;
	switch ( chip_size ) {
	case SMALL_CHAR_GRAPH_SIZE:
		type = ItemMoney::TYPE_PETTY;
		break;
	case NORMAL_CHAR_GRAPH_SIZE:
		type = ItemMoney::TYPE_BAG;
		break;
	case BIG_CHAR_GRAPH_SIZE:
		type = ItemMoney::TYPE_500;
		break;
	}
	Vector pos = enemy->getPos( ) + Vector( 0, -chip_size );
	ItemPtr item = ItemPtr( new ItemMoney( pos, type ) );
	item->setState( enemy->getState( ) );
	Storage::getTask( )->add( item );
}
