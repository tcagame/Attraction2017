#include "ViewerDebug.h"
#include "Drawer.h"
#include "ace_define.h"
#include "Armoury.h"
#include "Shot.h"
#include "Military.h"
#include "Enemy.h"
#include "Family.h"
#include "Player.h"
#include "Map.h"
#include "MapEvent.h"

ViewerDebug::ViewerDebug( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_block = drawer->createImage( "Editor/block/block.png" );
}

ViewerDebug::~ViewerDebug( ) {
}

void ViewerDebug::draw( ) const {
	drawPlayer( );
	drawEnemy( );
	drawShot( );
	drawChip( );
}

void ViewerDebug::drawPlayer( ) const {
	FamilyPtr family( Family::getTask( ) );
	int camera_pos = ( int )family->getCameraPos( );
	DrawerPtr drawer( Drawer::getTask( ) );
	for ( int i = 0; i < ACE_PLAYER_NUM; i++ ) {
		PlayerConstPtr player = family->getPlayer( i );
		int add_sx = - camera_pos;
		int add_sy = VIEW_STREET_Y;
		if ( player->getState( ) == Character::STATE_EVENT ) {
			add_sx = 0;
			add_sy = VIEW_EVENT_Y;
		}
		Vector pos( player->getPos( ) - Vector( 0, player->getChip( ).size / 2 ) );
		drawer->drawCircle( pos + Vector( add_sx, add_sy ), player->getRadius( ) );
	}
}

void ViewerDebug::drawEnemy( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	FamilyPtr family( Family::getTask( ) );
	MilitaryPtr military( Military::getTask( ) );
	{//main
		int camera_pos = ( int )family->getCameraPos( );
		std::list< EnemyPtr > enemies = military->getEnemyList( );
		std::list< EnemyPtr >::const_iterator ite = enemies.begin( );
		int enemy_num = 0;
		while ( ite != enemies.end( ) ) {
			EnemyPtr enemy = ( *ite );
			if ( !enemy ) {
				ite++;
				continue;
			}
			Vector pos( enemy->getPos( ) - Vector( camera_pos, enemy->getChipSize( ) / 2 ) );
			drawer->drawCircle( pos + Vector( 0, VIEW_STREET_Y ), enemy->getRadius( ) );
			enemy_num++;
			ite++;
		}
		drawer->drawString( 0, 20, "Enemy-Street:%d", enemy_num );
	}
	{//event
		std::list< EnemyPtr > enemies = military->getEventEnemyList( );
		std::list< EnemyPtr >::const_iterator ite = enemies.begin( );
		int enemy_num = 0;
		while ( ite != enemies.end( ) ) {
			EnemyPtr enemy = ( *ite );
			if ( !enemy ) {
				ite++;
				continue;
			}
			Vector pos( enemy->getPos( ) - Vector( 0, enemy->getChipSize( ) / 2 ) );
			drawer->drawCircle( pos + Vector( 0, VIEW_EVENT_Y ), enemy->getRadius( ) );
			enemy_num++;
			ite++;
		}
		drawer->drawString( 0, 0, "Enemy-Event:%d", enemy_num );
	}
	{//boss
		EnemyPtr boss = military->getBoss( );
		if ( boss ) {
			Vector pos( boss->getPos( ) - Vector( 0, boss->getChipSize( ) / 2 ) );
			drawer->drawCircle( pos + Vector( 0, VIEW_EVENT_Y ), boss->getRadius( ) );
		}
	}
}

void ViewerDebug::drawShot( ) const {
	FamilyPtr family( Family::getTask( ) );
	int camera_pos = ( int )family->getCameraPos( );
	DrawerPtr drawer( Drawer::getTask( ) );
	ArmouryPtr armoury( Armoury::getTask( ) );
	for ( int i = 0; i < armoury->getMaxShotNum( ); i++ ) {
		ShotConstPtr shot = armoury->getShot( i );
		if ( !shot ) {
			continue;
		}
		int add_sx = -camera_pos;
		int add_sy = VIEW_STREET_Y;
		if ( shot->getState( ) == Character::STATE_EVENT ) {
			add_sx = 0;
			add_sy = VIEW_EVENT_Y;
		}
		Vector pos( shot->getPos( ) - Vector( 0, shot->getChip( ).size / 2 ) );
		drawer->drawCircle( pos + Vector( add_sx, add_sy ), shot->getRadius( ) );
	}
}

void ViewerDebug::drawChip( ) const {
	FamilyPtr family( Family::getTask( ) );
	int camera_pos = ( int )family->getCameraPos( );
	DrawerPtr drawer( Drawer::getTask( ) );
	{//main
		MapPtr map( Map::getTask( ) );
		//const int MAP_WIDTH = map->getPageNum( ) * PAGE_OBJECT_WIDTH_NUM * OBJECT_CHIP_SIZE;
		//表示する横の数
		int width = 8 * PAGE_OBJECT_WIDTH_NUM;
		for ( int i = 0; i < width; i++ ) {
			for ( int j = 0; j < OBJECT_CHIP_HEIGHT_NUM; j++ ) {
				int x = i * OBJECT_CHIP_SIZE - camera_pos % OBJECT_CHIP_SIZE;
				int y = j * OBJECT_CHIP_SIZE;
				Vector pos = Vector( x + camera_pos + OBJECT_CHIP_SIZE / 2, y + OBJECT_CHIP_SIZE / 2 );

				unsigned char obj = map->getObject( pos );
				if ( obj == OBJECT_BLOCK ) {
					_block->setRect( 0, 16, OBJECT_CHIP_SIZE, OBJECT_CHIP_SIZE );
					_block->setPos( x, y + VIEW_STREET_Y );
					_block->draw( );
				}
				if ( obj == OBJECT_ONEWAY ) {
					_block->setRect( 16, 0, OBJECT_CHIP_SIZE, OBJECT_CHIP_SIZE );
					_block->setPos( x, y + VIEW_STREET_Y );
					_block->draw( );
				}
				if ( obj >= OBJECT_EVENT_REDDEAMON ) {
					_block->setRect( 32, 0, OBJECT_CHIP_SIZE, OBJECT_CHIP_SIZE );
					_block->setPos( x, y + VIEW_STREET_Y );
					_block->draw( );
				}
			}
		}
	}
	{//event
		int width = 8 * PAGE_OBJECT_WIDTH_NUM;
		MapEventPtr map( MapEvent::getTask( ) );
		if ( map->getType( ) != MapEvent::TYPE_TITLE ) {
			for ( int i = 0; i < width; i++ ) {
				for ( int j = 0; j < OBJECT_CHIP_HEIGHT_NUM; j++ ) {
					int x = i * OBJECT_CHIP_SIZE;
					int y = j * OBJECT_CHIP_SIZE;
					Vector pos = Vector( x + OBJECT_CHIP_SIZE / 2, y + OBJECT_CHIP_SIZE / 2 );

					unsigned char obj = map->getObject( pos );
					if ( obj == OBJECT_BLOCK ) {
						_block->setRect( 0, 16, OBJECT_CHIP_SIZE, OBJECT_CHIP_SIZE );
						_block->setPos( x, y + VIEW_EVENT_Y );
						_block->draw( );
					}
					if ( obj == OBJECT_ONEWAY ) {
						_block->setRect( 16, 0, OBJECT_CHIP_SIZE, OBJECT_CHIP_SIZE );
						_block->setPos( x, y + VIEW_EVENT_Y );
						_block->draw( );
					}
					if ( obj >= OBJECT_EVENT_REDDEAMON ) {
						_block->setRect( 32, 0, OBJECT_CHIP_SIZE, OBJECT_CHIP_SIZE );
						_block->setPos( x, y + VIEW_EVENT_Y );
						_block->draw( );
					}
				}
			}
		}
	}
}

