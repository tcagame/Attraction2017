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

ViewerDebug::ViewerDebug( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_block = drawer->createImage( "Editor/block/block.png" );
}

ViewerDebug::~ViewerDebug( ) {
}

void ViewerDebug::draw( ) const {
	FamilyPtr family( Family::getTask( ) );
	int camera_pos = ( int )family->getCameraPos( );
	DrawerPtr drawer( Drawer::getTask( ) );
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
		Vector pos( player->getPos( ) - Vector( camera_pos, player->getChip( ).size / 2 ) );
		drawer->drawCircle( pos + Vector( 0, VIEW_STREET_Y ), player->getRadius( ) );
	}
}

void ViewerDebug::drawEnemy( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	FamilyPtr family( Family::getTask( ) );
	int camera_pos = ( int )family->getCameraPos( );
	std::list< EnemyPtr > enemies = Military::getTask( )->getList( );
	std::list< EnemyPtr >::const_iterator ite = enemies.begin( );
	int enemy_num = 0;
	while ( ite != enemies.end( ) ) {
		EnemyPtr enemy = ( *ite );
		if ( !enemy ) {
			ite++;
			continue;
		}
		Vector pos( enemy->getPos( ) - Vector( camera_pos, enemy->getChip( ).size / 2 ) );
		drawer->drawCircle( pos + Vector( 0, VIEW_STREET_Y ), enemy->getRadius( ) );
		enemy_num++;
		ite++;
	}
	drawer->drawString( 0, 0, "Enemy:%d", enemy_num );
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
		Vector pos( shot->getPos( ) - Vector( camera_pos, shot->getChip( ).size / 2 ) );
		drawer->drawCircle( pos + Vector( 0, VIEW_STREET_Y ), shot->getRadius( ) );
	}
}

void ViewerDebug::drawChip( ) const {
	FamilyPtr family( Family::getTask( ) );
	int camera_pos = ( int )family->getCameraPos( );
	DrawerPtr drawer( Drawer::getTask( ) );
	MapPtr map( Map::getTask( ) );
	const int MAP_WIDTH = map->getPageNum( ) * PAGE_OBJECT_WIDTH_NUM * OBJECT_CHIP_SIZE;
	int width = ( SCREEN_WIDTH / GRAPH_SIZE + 1 ) * PAGE_OBJECT_WIDTH_NUM;
	for ( int i = 0; i < width; i++ ) {
		for ( int j = 0; j < OBJECT_CHIP_HEIGHT_NUM; j++ ) {
			Vector pos( i * OBJECT_CHIP_SIZE + camera_pos, j * OBJECT_CHIP_SIZE );
			if ( map->isExistance( pos + Vector( OBJECT_CHIP_SIZE / 2, OBJECT_CHIP_SIZE / 2 ) ) ) {
				_block->setRect( 0, 16, OBJECT_CHIP_SIZE, OBJECT_CHIP_SIZE );
				_block->setPos( i * OBJECT_CHIP_SIZE - ( camera_pos % OBJECT_CHIP_SIZE ), j * OBJECT_CHIP_HEIGHT_NUM + VIEW_STREET_Y );
				_block->draw( );
			}
		}
	}
}

