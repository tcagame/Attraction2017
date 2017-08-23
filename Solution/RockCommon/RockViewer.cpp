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
#include "Effect.h"

RockViewerPtr RockViewer::getTask( ) {
	return std::dynamic_pointer_cast< RockViewer >( Application::getInstance( )->getTask( getTag( ) ) );
}


RockViewer::RockViewer( StatusPtr status ) :
_status( status ) {
}


RockViewer::~RockViewer( ) {
}

void RockViewer::update( ) {
	DrawerPtr drawer = Drawer::getTask( );
	drawer->flip( );
	drawMap( );
	drawEnemy( );
	drawPlayer( );
	drawShot( );
	drawItem( );
	Effect::getTask( )->drawEffect( );
}

void RockViewer::drawMap( ) const {
	std::vector< ModelMV1Ptr > models = RockMap::getTask( )->getColModels( );
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

