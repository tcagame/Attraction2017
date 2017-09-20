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

const int MAX_POP = 50;
PTR( Player );

MilitaryPtr Military::getTask( ) {
	return std::dynamic_pointer_cast< Military >( Application::getInstance( )->getTask( getTag( ) ) );
}


Military::Military( ) {
}


Military::~Military( ) {
}

void Military::initialize( ) {
	_hell_fire = EnemyPtr( new EnemyHellFire( Vector( 64, 64 ) ) );
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
		PlayerPtr overlapped_player = family->getOverlappedPlayer( enemy );
		if ( overlapped_player ) {
			if ( overlapped_player->isOnHead( enemy ) ) {
				overlapped_player->bound( );
			} else {
				int force = enemy->getForce( );
				if ( force > 0 ) {
					overlapped_player->damage( force );
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
	if ( ( int )_enemies.size( ) > MAX_POP ) {
		return;
	}
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
	int size = enemy->getChipSize( );
	//エネミーの大きさで金の量を変える
	unsigned char type = OBJECT_MONEY_PURSE;
	if ( size <= SMALL_CHAR_GRAPH_SIZE ) {
		type = OBJECT_MONEY_PURSE;
	} else {
		if ( size <= NORMAL_CHAR_GRAPH_SIZE ) {
			type = OBJECT_MONEY_BAG;
		} else {
			if ( size <= BIG_CHAR_GRAPH_SIZE ) {
				type = OBJECT_MONEY_500;
			}
		}
	}
	Vector pos = enemy->getPos( ) + Vector( 0, -size );
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
