#include "ViewerDebug.h"
#include "Drawer.h"
#include "Device.h"
#include "ace_define.h"
#include "Armoury.h"
#include "Shot.h"
#include "Military.h"
#include "Enemy.h"
#include "Family.h"
#include "Player.h"
#include "Monmotaro.h"
#include "World.h"
#include "Map.h"
#include "Server.h"

ViewerDebug::ViewerDebug( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_block = drawer->createImage( "Editor/block/block.png" );
}

ViewerDebug::~ViewerDebug( ) {
}

void ViewerDebug::draw( ) {
	FamilyPtr family = Family::getTask( );
	family->pushDebugData( _data );

	MilitaryPtr military = Military::getTask( );
	military->pushDebugData( _data );

	ArmouryPtr armoury = Armoury::getTask( );
	armoury->pushDebugData( _data );

	pushMessageConnect( );

	drawChip( );
	drawCircle( );
	drawMessage( );
}

void ViewerDebug::drawChip( ) {
	FamilyPtr family( Family::getTask( ) );
	int camera_pos = family->getCameraPosX( );
	DrawerPtr drawer( Drawer::getTask( ) );
	{//main
		MapPtr map = World::getTask( )->getMap( AREA_STREET );
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
				if ( obj == OBJECT_WATER ) {
					_block->setRect( 32, 16, OBJECT_CHIP_SIZE, OBJECT_CHIP_SIZE );
					_block->setPos( x, y + VIEW_STREET_Y );
					_block->draw( );
				}
				if ( obj >= OBJECT_EVENT_REDDAEMON ) {
					_block->setRect( 32, 0, OBJECT_CHIP_SIZE, OBJECT_CHIP_SIZE );
					_block->setPos( x, y + VIEW_STREET_Y );
					_block->draw( );
				}
			}
		}
	}
	{//event
		int width = 8 * PAGE_OBJECT_WIDTH_NUM;
		WorldPtr world = World::getTask( );
		MapPtr map = World::getTask( )->getMap( AREA_EVENT );
		if ( world->getEvent( ) != EVENT_TITLE ) {
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
					if ( obj == OBJECT_WATER ) {
						_block->setRect( 32, 16, OBJECT_CHIP_SIZE, OBJECT_CHIP_SIZE );
						_block->setPos( x, y + VIEW_EVENT_Y );
						_block->draw( );
					}
					//イベントブロックの場合(ここにはありえない)
					if ( obj >= OBJECT_EVENT_REDDAEMON ) {
						_block->setRect( 32, 0, OBJECT_CHIP_SIZE, OBJECT_CHIP_SIZE );
						_block->setPos( x, y + VIEW_EVENT_Y );
						_block->draw( );
					}
				}
			}
		}
	}
}

void ViewerDebug::pushMessageConnect( ) {
	ServerPtr server( Server::getTask( ) );
	for ( int i = 0; i < Server::MAX_MACHINES; i++ ) {
		_data.message.push_back( "IP:" + server->getMachineIPStr( i ) );
	}
}

void ViewerDebug::drawCircle( ) {
	DrawerPtr drawer = Drawer::getTask( );
	for ( Data::Circle circle : _data.circle ) {
		drawer->drawCircle( circle.pos, circle.radius );
	}
	_data.circle.clear( );
}

void ViewerDebug::drawMessage( ) {
	DrawerPtr drawer = Drawer::getTask( );
	int y = 0;
	for ( std::string message : _data.message ) {
		drawer->drawString( 0, y, message.c_str( ) );
		y += 20;
	}
	_data.message.clear( );
}