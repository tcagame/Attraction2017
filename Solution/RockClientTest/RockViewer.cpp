#include "RockViewer.h"
#include "Drawer.h"
#include "Application.h"
#include "RockMilitary.h"
#include "RockEnemy.h"
#include "RockMap.h"
#include "RockDollHouse.h"
#include "RockFamily.h"
#include "RockPlayer.h"

RockViewerPtr RockViewer::getTask( ) {
	return std::dynamic_pointer_cast< RockViewer >( Application::getInstance( )->getTask( getTag( ) ) );
}


RockViewer::RockViewer( ) {
}


RockViewer::~RockViewer( ) {
}

void RockViewer::update( ) {
	DrawerPtr drawer = Drawer::getTask( );
	drawer->flip( );
	drawMap( );
	drawEnemy( );
	drawPlayer( );
}

void RockViewer::drawMap( ) const {
	ModelMV1Ptr model = RockMap::getTask( )->getModel( );
	model->draw( );
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
		DOLL doll = enemy->getDoll( );
		Vector pos = enemy->getPos( );
		ModelMV1Ptr model = doll_house->getModel( doll );
		model->setTrans( Matrix::makeTransformTranslation( pos ) );
		model->draw( );
		ite++;
	}
}

void RockViewer::drawPlayer( ) const {
	RockDollHousePtr doll_house( RockDollHouse::getTask( ) );
	RockFamilyPtr family( RockFamily::getTask( ) );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		RockPlayerPtr player( family->getPlayer( i ) );
		DOLL doll = player->getDoll( );
		Vector pos = player->getPos( );
		ModelMV1Ptr model = doll_house->getModel( doll );
		double anim_time = fmod( player->getAnimTime( ), model->getEndAnimTime( ) );
		model->setAnimTime( anim_time );
		model->setTrans( Matrix::makeTransformTranslation( pos ) );
		model->draw( );
	}
}

