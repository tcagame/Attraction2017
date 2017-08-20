#include "Military.h"
#include "Application.h"
#include "ace_define.h"
#include "Family.h"
#include "Player.h"
#include "EnemyBossRedDaemon.h"
#include "EnemyBossBloodDaemon.h"
#include "EnemyBossMonsterTree.h"
#include "EnemyBossRock.h"
#include "MapEvent.h"
#include "Impact.h"
#include "Storage.h"
#include "ItemMoney.h"
#include "EnemyHellFire.h"
#include "EnemyAttack.h"
#include "EnemyBoss.h"
#include "Magazine.h"

PTR( Player );

MilitaryPtr Military::getTask( ) {
	return std::dynamic_pointer_cast< Military >( Application::getInstance( )->getTask( getTag( ) ) );
}


Military::Military( ) {
	_hell_fire = EnemyPtr( new EnemyHellFire( Vector( 64, 64 ) ) );
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
			if ( enemy->isFinished( ) ) {
				//エネミーが倒れた場合、倒れた位置で爆発する
				if ( !std::dynamic_pointer_cast< EnemyAttack >( enemy ) ) {
					dropMoney( enemy );
				}
				
				int impact_chip_size = enemy->getChipSize( );
				Magazine::getTask( )->add( ImpactPtr( new Impact( enemy->getPos( ) + Vector( 0, enemy->getChipSize( ) / 2 ), Character::STATE_MAIN, impact_chip_size ) ) );
				ite = _enemies.erase( ite );
				continue;
			}
			if ( !enemy->isInScreen( ) ) {
				//エネミーが画面外に行くと消える
				ite = _enemies.erase( ite );
				continue;
			}
			for ( int i = 0; i < ACE_PLAYER_NUM; i++ ) {
				PlayerPtr player( family->getPlayer( i ) );
				if ( player->isOverlapped( enemy ) ) {
					if ( player->isOnHead( enemy ) ) {
						player->bound( );
					} else {
						int force = enemy->getForce( );
						if ( force > 0 ) {
							player->damage( force );
						}
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
				_boss->dropItem( );
				int impact_chip_size = _boss->getChipSize( ) * 2;
				Magazine::getTask( )->add( ImpactPtr( new Impact( _boss->getPos( ) + Vector( 0, _boss->getChipSize( ) / 2 ), Character::STATE_EVENT, impact_chip_size ) ) );
				_boss = EnemyBossPtr( );
			}
		}
		std::list< EnemyPtr >::const_iterator ite = _event_enemies.begin( );
		while ( ite != _event_enemies.end( ) ) {
			EnemyPtr enemy = (*ite);
			if ( !enemy ) {
				ite++;
				continue;
			}
			if ( enemy->isFinished( ) ) {
				//エネミーが倒れた場合、倒れた位置で爆発する
				if ( !std::dynamic_pointer_cast< EnemyAttack >( enemy ) ) {
					dropMoney( enemy );
				}
				int impact_chip_size = enemy->getChipSize( );
				Magazine::getTask( )->add( ImpactPtr( new Impact( enemy->getPos( ) + Vector( 0, enemy->getChipSize( ) / 2 ), Character::STATE_MAIN, impact_chip_size ) ) );
				ite = _event_enemies.erase( ite );
				continue;
			}
			if ( !enemy->isInScreen( ) ) {
				//エネミーが画面外に行くと消える
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
	//地獄火
	_hell_fire->update( );
	for ( int i = 0; i < ACE_PLAYER_NUM; i++ ) {
		PlayerPtr player( family->getPlayer( i ) );
		if ( player->isOverlapped( _hell_fire ) ) {
			//player->damage( 3 );
			player->blowAway( );
		}
	}
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
	Storage::getTask( )->eraseEventItem( );
	_event_enemies.clear( );
	switch ( type ) {
	case MapEvent::TYPE_TITLE:
		_boss = EnemyBossPtr( );
		break;
	case MapEvent::TYPE_RED_DAEMON:
		_boss = EnemyBossPtr( new EnemyBossRedDaemon( Vector( 800, 200 ) ) );
		break;
	case MapEvent::TYPE_FIRE:
		_boss = EnemyBossPtr( new EnemyBossBloodDaemon( Vector( 800, 200 ) ) );
		break;
	case MapEvent::TYPE_TREE:
		_boss = EnemyBossPtr( new EnemyBossMonsterTree( Vector( 800, 225 ) ) );
		break;
	case MapEvent::TYPE_ROCK:
		_boss = EnemyBossPtr( new EnemyBossRock( Vector( 800, 225 ) ) );
		break;
	}
}

EnemyPtr Military::getBoss( ) const {
	return _boss;
}

EnemyPtr Military::getHellFire( ) const {
	return _hell_fire;
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
