#include "Military.h"
#include "Application.h"
#include "ace_define.h"
#include "Family.h"
#include "Player.h"
#include "EnemyBossRedDaemon.h"
#include "EnemyBossBloodDaemon.h"
#include "EnemyBossMonsterTree.h"
#include "EnemyBossRock.h"
#include "Impact.h"
#include "Storage.h"
#include "ItemMoney.h"
#include "EnemyHellFire.h"
#include "EnemyAttack.h"
#include "EnemyBoss.h"
#include "Magazine.h"
#include "SynchronousData.h"
#include "World.h"
#include "Sound.h"
#include "Drawer.h"


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
	updateEnemy( );
	updateHellFire( );
}


void Military::updateEnemy( ) {
	std::list< EnemyPtr >::const_iterator ite = _enemies.begin( );
	FamilyPtr family( Family::getTask( ) );
	int camera_pos = family->getCameraPosX( );
	while ( ite != _enemies.end( ) ) {
		EnemyPtr enemy = (*ite);
		enemy->update( );
		enemy->setSynchronousData( camera_pos );

		//エネミーが倒れたときの処理
		if ( enemy->getPower( ) <= 0 ) {
			if ( !std::dynamic_pointer_cast< EnemyAttack >( enemy ) ) {
				dropMoney( enemy );
			}
			int impact_chip_size = enemy->getChipSize( ) * 2;
			Magazine::getTask( )->add( ImpactPtr( new Impact( enemy->getPos( ) + Vector( 0, enemy->getChipSize( ) / 2 ), enemy->getArea( ), impact_chip_size ) ) );
			ite = _enemies.erase( ite );
			continue;
		}

		//エネミーが画面外に行った時の処理
		if ( !enemy->isInScreen( ) ) {
			ite = _enemies.erase( ite );
			continue;
		}

		//プレイヤーと接触したときの処理
		for ( int i = 0; i < MAX_PLAYER; i++ ) {
			PlayerPtr player( family->getPlayer( i ) );
			if ( !player->isExist( ) ) {
				continue;
			}
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
		ite++;
	}
}

void Military::updateHellFire( ) {
	FamilyPtr family( Family::getTask( ) );
	int camera_pos = family->getCameraPosX( );

	_hell_fire->update( );
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		PlayerPtr player( family->getPlayer( i ) );
		if ( player->isOverlapped( _hell_fire ) ) {
			//player->damage( 3 );
			player->blowAway( );
		}
	}
	_hell_fire->setSynchronousData( camera_pos );
}

const std::list< EnemyPtr > Military::getEnemyList( ) const {
	return _enemies;
}

void Military::popUp( EnemyPtr enemy ) {
	_enemies.push_back( enemy );
}

EnemyPtr Military::getOverlappedEnemy( CharacterConstPtr character ) const {
	EnemyPtr result = EnemyPtr( );
	AREA area_character = character->getArea( );
	std::list< EnemyPtr >::const_iterator ite = _enemies.begin( );
	while ( ite != _enemies.end( ) ) {
		EnemyPtr enemy = (*ite);
		if ( enemy->getArea( ) != area_character ) {
			ite++;
			continue;
		}
		if ( enemy->isOverlapped( character ) ) {
			result = enemy;
			break;
		}
		ite++;
	}

	return result;
}

void Military::eraseEventEnemy( ) {
	std::list< EnemyPtr >::iterator ite = _enemies.begin( );
	while ( ite != _enemies.end( ) ) {
		EnemyPtr enemy = (*ite);
		if ( enemy->getArea( ) == AREA_EVENT ) {
			ite = _enemies.erase( ite );
			continue;
		}
		ite++;
	}
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
	ItemPtr item = ItemPtr( new ItemMoney( pos, type, enemy->getArea( ) ) );
	Storage::getTask( )->add( item );
}


void Military::pushDebugData( ViewerDebug::Data& data ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	FamilyPtr family( Family::getTask( ) );
	MilitaryPtr military( Military::getTask( ) );
	int camera_pos = family->getCameraPosX( );

	std::list< EnemyPtr >::const_iterator ite = _enemies.begin( );

	while ( ite != _enemies.end( ) ) {
		EnemyPtr enemy = ( *ite );
		data.circle.push_back( enemy->getDebugDataCircle( ) );
		ite++;
	}

	data.circle.push_back( _hell_fire->getDebugDataCircle( ) );
	data.message.push_back( "Enemy:" + std::to_string( _enemies.size( ) ) );
}

void Military::shiftPos( int map_width ) {
	std::list< EnemyPtr >::iterator ite = _enemies.begin( );
	while ( ite != _enemies.end( ) ) {
		EnemyPtr enemy = (*ite);
		enemy->shiftPos( map_width );
		ite++;
	}
	_hell_fire->shiftPos( map_width );
}
