#include "RockViewer.h"
#include "Drawer.h"
#include "Application.h"
#include "RockMilitary.h"
#include "RockEnemy.h"
#include "RockMap.h"
#include "RockDollHouse.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockClientInfo.h"
#include "Status.h"

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
	unsigned int client_id = RockClientInfo::getTask( )->getClientId( );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		if ( client_id != _status->getPlayer( i ).state ) {
			continue;
		}
		RockPlayerPtr player( family->getPlayer( i ) );
		DOLL doll = player->getDoll( );
		Vector pos = player->getPos( );
		ModelMV1Ptr model = doll_house->getModel( doll );
		double anim_time = fmod( player->getAnimTime( ), model->getEndAnimTime( ) );
		if ( ( doll == DOLL_GARISUKE_DEAD ||
			   doll == DOLL_TAROSUKE_DEAD ||
			   doll == DOLL_TAROJIRO_DEAD ||
			   doll == DOLL_TAROMI_DEAD ) &&
			   ( player->getAnimTime( ) >= model->getEndAnimTime( ) ) ) {
			//死亡アニメーションはループさせない
			anim_time = model->getEndAnimTime( );
		}
		model->setAnimTime( anim_time );
		model->setTrans( Matrix::makeTransformTranslation( pos ) );
		model->draw( );
	}
}

