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
	//プレイヤー
	for ( int i = 0; i < ACE_PLAYER_NUM; i++ ) {
		PlayerConstPtr player = family->getPlayer( i );
		drawer->drawCircle( Vector( player->getPos( ) - Vector( camera_pos, player->getChip( ).size / 2 ) ), player->getRadius( ) );
	}
	//エネミー
	std::list< EnemyPtr > enemies = Military::getTask( )->getList( );
	std::list< EnemyPtr >::const_iterator ite = enemies.begin( );	
	while ( ite != enemies.end( ) ) {
		EnemyPtr enemy = ( *ite );
		if ( !enemy ) {
			ite++;
			continue;
		}
		drawer->drawCircle( Vector( enemy->getPos( ) - Vector( camera_pos, enemy->getChip( ).size / 2 ) ), enemy->getRadius( ) );
		ite++;
	}
	//妖怪念力
	ArmouryPtr armoury( Armoury::getTask( ) );
	for ( int i = 0; i < armoury->getMaxShotNum( ); i++ ) {
		ShotConstPtr shot = armoury->getShot( i );
		if ( !shot ) {
			continue;
		}
		drawer->drawCircle( Vector( shot->getPos( ) - Vector( camera_pos, shot->getChip( ).size / 2 ) ), shot->getRadius( ) );
	}
	//チップ
	MapPtr map( Map::getTask( ) );
	const int MAP_WIDTH = map->getPageNum( ) * PAGE_OBJECT_WIDTH_NUM * OBJECT_CHIP_SIZE;
	for ( int i = 0; i < map->getPageNum( ) * PAGE_OBJECT_WIDTH_NUM; i++ ) {
		for ( int j = 0; j < OBJECT_CHIP_HEIGHT_NUM; j++ ) {
			Vector pos( i * OBJECT_CHIP_SIZE, VIEW_STREET_Y + j * OBJECT_CHIP_SIZE );
			if ( map->isExistance( pos + Vector( 1, 1 ) * ( OBJECT_CHIP_SIZE / 2 ) ) ) {
				_block->setRect( 0, 16, OBJECT_CHIP_SIZE, OBJECT_CHIP_SIZE );
				if ( ( int )pos.x - camera_pos < -OBJECT_CHIP_SIZE ) {
					pos.x += MAP_WIDTH + MAP_WIDTH * ( camera_pos / MAP_WIDTH );
				}
				_block->setPos( ( int )pos.x - camera_pos, ( int )pos.y );
				_block->draw( );
			}
		}
	}
}