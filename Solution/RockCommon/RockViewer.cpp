#include "RockViewer.h"
#include "Drawer.h"
#include "Application.h"
#include "RockMilitary.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockEnemy.h"
#include "RockMap.h"
#include "RockDollHouse.h"
#include "RockClientInfo.h"
#include "Status.h"
#include "Drawer.h"
#include "RockArmoury.h"
#include "RockStorage.h"
#include "RockItem.h"
#include "RockShot.h"
#include "RockImpact.h"
#include "RockCasket.h"
#include "Effect.h"
#include "RockAlter.h"
#include "RockAncestors.h"
#include "Movie.h"
#include "RockTheater.h"

const int DRAW_UI_Y = 512;
const int HP_GRAPH_HEIGHT = 16;
const int HP_GRAPH_WIDTH = 8;
const int MONEY_GRAPH_HEIGHT = 16;
const int MONEY_GRAPH_WIDTH = 12;
const int MONEY_Y = DRAW_UI_Y + 102;

RockViewerPtr RockViewer::getTask( ) {
	return std::dynamic_pointer_cast< RockViewer >( Application::getInstance( )->getTask( getTag( ) ) );
}


RockViewer::RockViewer( StatusPtr status ) :
_status( status ) {
}


RockViewer::~RockViewer( ) {
}

void RockViewer::initialize( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_status_flame = drawer->createImage( "UI/status_plate.png" );
	_status_ui = drawer->createImage( "UI/ui.png" );
	_status_num = drawer->createImage( "UI/ui_num.png" );
}

void RockViewer::update( ) {
	DrawerPtr drawer = Drawer::getTask( );
	drawer->waitForSync( );
	drawer->flip( );
	drawMap( );
	drawEnemy( );
	drawPlayer( );
	drawAncestors( );
	//drawShot( );
	drawItem( );
	drawAlter( );
	drawCasket( );
	drawUI( );
	drawMovie( );
	Effect::getTask( )->drawEffect( );
}

void RockViewer::drawMap( ) const {
	std::vector< ModelMV1Ptr > models = RockMap::getTask( )->getModels( );
	int size = ( int )models.size( );
	for ( int i = 0; i < size; i++ ) {
		models[ i ]->draw( );
	}
}

void RockViewer::drawEnemy( ) const {
	RockDollHousePtr doll_house( RockDollHouse::getTask( ) );
	std::list< RockEnemyPtr > enemies = RockMilitary::getTask( )->getEnemyList( );
	std::list< RockEnemyPtr >::iterator ite = enemies.begin( );
	while ( ite != enemies.end( ) ) {
		RockEnemyPtr enemy = (*ite);
		if ( !enemy ) {
			ite++;
			continue;
		}
		ModelMV1Ptr model = enemy->getModel( );
		model->draw( );
		ite++;
	}
}

void RockViewer::drawPlayer( ) const {
	RockFamilyPtr family( RockFamily::getTask( ) );
	unsigned int client_id = RockClientInfo::getTask( )->getClientId( );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		if ( client_id != _status->getPlayer( i ).area ) {
			continue;
		}
		ModelMV1Ptr model = family->getPlayer( i )->getModel( );
		model->draw( );
	}
}

void RockViewer::drawAncestors( ) const {
	RockFamilyPtr family( RockFamily::getTask( ) );
	unsigned int client_id = RockClientInfo::getTask( )->getClientId( );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		RockAncestorsPtr ancestors = family->getAncestors( i );
		if ( client_id != _status->getPlayer( i ).area ||
			 !ancestors->isActive( ) ) {
			continue;
		}
		ModelMV1Ptr model = ancestors->getModel( );
		model->draw( );
	}
}



void RockViewer::drawShot( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	RockArmouryPtr armoury( RockArmoury::getTask( ) );
	std::list< RockShotPtr > shots = armoury->getShots( );
	std::list< RockShotPtr >::const_iterator ite = shots.begin( );
	while ( ite != shots.end( ) ) {
		RockShotPtr shot = *ite;
		if ( !shot ) {
			ite++;
			continue;
		}

		Vector pos = shot->getPos( );
		drawer->drawLine( pos, pos + Vector( 0, 10, 0 ) );
		ite++;
	}
}

void RockViewer::drawItem( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	RockStoragePtr storage( RockStorage::getTask( ) );
	std::list< RockItemPtr > items = storage->getItems( );
	std::list< RockItemPtr >::const_iterator ite = items.begin( );
	while ( ite != items.end( ) ) {
		RockItemPtr item = *ite;
		if ( !item ) {
			ite++;
			continue;
		}
		ModelMV1Ptr model = item->getModel( );
		model->draw( );
		ite++;
	}
}

void RockViewer::drawAlter( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	RockStoragePtr storage( RockStorage::getTask( ) );
	std::list< RockAlterPtr > alters = storage->getAlters( );
	std::list< RockAlterPtr >::const_iterator ite = alters.begin( );
	while ( ite != alters.end( ) ) {
		RockAlterPtr alter = *ite;
		if ( !alter ) {
			ite++;
			continue;
		}
		ModelMV1Ptr model = alter->getModel( );
		model->draw( );
		ite++;
	}
}

void RockViewer::drawCasket( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	RockStoragePtr storage( RockStorage::getTask( ) );
	std::list< RockCasketPtr > casket = storage->getCaskets( );
	std::list< RockCasketPtr >::const_iterator ite = casket.begin( );
	while ( ite != casket.end( ) ) {
		RockCasketPtr casket = *ite;
		if ( !casket ) {
			ite++;
			continue;
		}
		ModelMV1Ptr model = casket->getModel( );
		model->draw( );
		ite++;
	}
}


void RockViewer::drawUI( ) const {
	RockFamilyPtr family( RockFamily::getTask( ) );
	unsigned int client_id = RockClientInfo::getTask( )->getClientId( );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		if ( client_id != _status->getPlayer( i ).area ) {
			continue;
		}
		int sx = i * 320;
		_status_flame->setPos( sx, DRAW_UI_Y );
		_status_flame->draw( );

		//(POWER)
		int tw = HP_GRAPH_WIDTH * _status->getPlayer( i ).power;
		_status_ui->setRect( 0, 256, tw, HP_GRAPH_HEIGHT );
		sx += 160;
		int sy = DRAW_UI_Y + 50;
		_status_ui->setPos( sx, sy );
		_status_ui->draw( );
		//(MONEY)
		int money = _status->getPlayer( i ).money;
		int digit = 0;
		while( money > 0 ) {
			digit++;
			money /= 10;
		}
		for ( int j = 0; j < digit; j++ ) {
			int num = _status->getPlayer( i ).money % (int)pow( 10.0, (double)j + 1 );
			num /= (int)pow( 10.0, (double)j );
			_status_num->setRect( MONEY_GRAPH_WIDTH * num, 0, MONEY_GRAPH_WIDTH, MONEY_GRAPH_HEIGHT );
			_status_num->setPos( -j * MONEY_GRAPH_WIDTH + 275, MONEY_Y );
			_status_num->draw( );
		}
	}
}

void RockViewer::drawMovie( ) const {
	RockTheaterPtr theater = RockTheater::getTask( );
	if ( !theater ) {
		return;
	}
	MoviePtr movie = theater->getMovie( );
	if ( movie->isPlay( ) ) {
		movie->draw( );
	}
}
