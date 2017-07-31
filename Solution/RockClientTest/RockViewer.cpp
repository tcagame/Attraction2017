#include "RockViewer.h"
#include "Drawer.h"
#include "Application.h"
#include "RockMilitary.h"
#include "RockEnemy.h"
#include "RockMap.h"
#include "RockDollHouse.h"

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
		DOLL id = enemy->getId( );
		Vector pos = enemy->getPos( );
		ModelMV1Ptr model = doll_house->getModel( id );
		model->setTrans( Matrix::makeTransformTranslation( pos ) );
		model->draw( );
		ite++;
	}
}
