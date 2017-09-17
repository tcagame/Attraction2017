#include "RockMapStreet.h"
#include "RockMapStreetDrawer.h"
#include "RockCamera.h"
#include "Status.h"
#include "MessageSender.h"
//Player
#include "RockFamily.h"
#include "RockPlayer.h"
//shot
#include "RockArmoury.h"
#include "RockShot.h"
//Item
#include "RockStorage.h"
#include "RockItemToku.h"
#include "RockItemMoney.h"
//EventObj
#include "RockAlter.h"
#include "RockCasket.h"
//EventChara
#include "RockOffice.h"
#include "RockEventTurtle.h"
#include "RockEventMiko.h"
#include "RockEventObaba.h"
#include "RockEventOtohime.h"
//Enemy
#include "RockMilitary.h"
#include "RockEnemyGhost.h"
#include "RockEnemyRedBard.h"
#include "RockEnemyWaterGhost.h"
#include "RockEnemyFaceAndHand.h"
#include "RockEnemyBat.h"
#include "RockEnemyKimono.h"
#include "RockEnemyCloud.h"
#include "RockEnemySkeleton.h"

const int REMOVE_CAVE_TIME = 500;
const int DROP_TIMING = 1800;

RockMapStreet::RockMapStreet( StatusPtr status ) :
_time( 0 ),
_virtue_pop( false ),
_status( status ) {
}

RockMapStreet::~RockMapStreet( ) {
}

void RockMapStreet::initialize( ) {
	loadStage( STAGE_STREET );
}

void RockMapStreet::update( ) {
	switch ( _stage ) {
	case STAGE_STREET:
		updateStreet( );
		break;
	case STAGE_CAVE:
		updateCave( );
		break;
	case STAGE_RYUGU:
		updateRyugu( );
		break;
	}
	if ( !isInActivePlayer( ) &&
		 _stage != STAGE_STREET ) {
		loadStage( STAGE_STREET );
	}
}

void RockMapStreet::updateStreet( ) {
	RockFamilyPtr family = RockFamily::getTask( );
	bool active = false;
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		RockPlayerPtr player = family->getPlayer( i );
		if ( !player->isActive( ) ) {
			continue;
		}
		active = true;
		{//鳥居へ行くとSTAGE_CAVEへ移動
			double length = ( Vector( -200, 0, -500 ) - player->getPos( ) ).getLength( );
			if ( length < 100 ) {
				loadStage( STAGE_CAVE );
			}
		}
		{//亀に乗ると竜宮城へ移動
			RockOfficePtr office = RockOffice::getTask( );
			std::list< RockEventCharacterPtr > eve_chara = office->getEventCharacters( );
			std::list< RockEventCharacterPtr >::iterator ite = eve_chara.begin( );
			while ( ite != eve_chara.end( ) ) {
				RockEventTurtlePtr turtle = std::dynamic_pointer_cast< RockEventTurtle >( *ite );
				if ( !turtle ) {
					ite++;
					continue;
				}
				if ( player->isOverLapped( turtle ) ) {
					if ( player->isOnHead( turtle ) ) {
						loadStage( STAGE_RYUGU );
						break;//whileを抜ける
					}
				}
				ite++;
			}
		}


		//STREET3のプレイヤーがいれば徳アイテムをポップ
		if ( !_virtue_pop ) {
			Status::Player status = _status->getPlayer( i );
			if ( status.area == AREA_STREET_3 ) {
				_virtue_pop = true;
				RockStoragePtr storage = RockStorage::getTask( );
				for ( int j = 0; j < 30; j++ ) {
					int interval = 200;
					storage->addItem( RockItemPtr( new RockItemToku( Vector( j * interval + interval / 2, 500, -500 - j * 10 ) ) ) );
				}
			}
		}
	}

	if ( !active ) {
		RockArmouryPtr armory( RockArmoury::getTask( ) );
		std::list< RockShotPtr > shots = armory->getShots( );
		std::list< RockShotPtr >::const_iterator ite = shots.begin( );
		while ( ite != shots.end( ) ) {
			RockShotPtr shot = *ite;
			if ( !shot ) {
				ite++;
				continue;
			}

			shot = RockShotPtr( );
			ite++;
		}

		armory->clearShot( );
	}
}

void RockMapStreet::updateCave( ) {
	_time++;
	RockFamilyPtr family = RockFamily::getTask( );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		RockPlayerPtr player = family->getPlayer( i );
		if ( !player->isActive( ) ) {
			continue;
		}

		if ( _time > REMOVE_CAVE_TIME ) {
			loadStage( STAGE_STREET );
			_time = 0;
		}
	}
}

void RockMapStreet::updateRyugu( ) {
	RockFamilyPtr family = RockFamily::getTask( );
	for( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		RockPlayerPtr player = family->getPlayer( i );
		if( !player->isActive( ) ) {
			continue;
		}
		{//亀に乗るとSTREET1へ移動
			RockOfficePtr office = RockOffice::getTask( );
			std::list< RockEventCharacterPtr > eve_chara = office->getEventCharacters( );
			std::list< RockEventCharacterPtr >::iterator ite = eve_chara.begin( );
			while ( ite != eve_chara.end( ) ) {
				RockEventTurtlePtr turtle = std::dynamic_pointer_cast< RockEventTurtle >( *ite );
				if ( !turtle ) {
					ite++;
					continue;
				}
				if ( player->isOverLapped( turtle ) ) {
					if ( player->isOnHead( turtle ) ) {
						loadStage( STAGE_STREET );
						break;//whileを抜ける
					}
				}
				ite++;
			}
		}
	}
}

RockMapStreet::STAGE RockMapStreet::getStage( ) const {
	return _stage;
}

void RockMapStreet::loadStage( STAGE next ) {
	genarateEnemies( next );
	genarateEventCharacters( next );
	genarateStorage( next );
	resetFamilyPos( next );
	_drawer.reset( new RockMapStreetDrawer( next ) );
	_stage = next;
}



void RockMapStreet::genarateEnemies( STAGE next ) {
	RockMilitaryPtr military = RockMilitary::getTask( );
	military->clean( );
	switch ( next ) {
	case STAGE_STREET:
		military->add( RockEnemyPtr( new RockEnemyRedBard    ( Vector(  800,  60, -520 ) ) ) );
		military->add( RockEnemyPtr( new RockEnemyWaterGhost ( Vector( 3800,  320, -530 ) ) ) );
		military->add( RockEnemyPtr( new RockEnemyWaterGhost ( Vector( 4100,  320, -700 ) ) ) );
		military->add( RockEnemyPtr( new RockEnemyWaterGhost ( Vector( 4700,  320, -680 ) ) ) );
		military->add( RockEnemyPtr( new RockEnemyCloud      ( Vector( 4500, 330, -650 ) ) ) );
		military->add( RockEnemyPtr( new RockEnemyCloud      ( Vector( 4900, 330, -650 ) ) ) );
		military->add( RockEnemyPtr( new RockEnemyBat        ( Vector( 2000, 190, -600 ) ) ) );
		military->add( RockEnemyPtr( new RockEnemyKimono     ( Vector( 2300, 200, -600 ) ) ) );
		break;
	case STAGE_CAVE:
		break;
	case STAGE_RYUGU:
		break;
	}
}

void RockMapStreet::genarateStorage( STAGE next ) {
	RockStoragePtr storage = RockStorage::getTask( );
	storage->clean( );
	switch ( next ) {
	case STAGE_STREET:
	{
		const int INTERVAL = 200;
		for ( int i = 0; i < 30; i++ ) {
			storage->addItem( RockItemPtr( new RockItemMoney( Vector( i * INTERVAL, 200, -500 - i * 10 ), 10000 ) ) );
		}
	}
		break;
	case STAGE_CAVE:
		break;
	case STAGE_RYUGU:
		storage->addCasket( RockCasketPtr( new RockCasket( Vector( -360, 400, 0 ) ) ) );
		break;
	}
}

void RockMapStreet::genarateEventCharacters( STAGE next ) {
	RockOfficePtr office = RockOffice::getTask( );
	office->clean( );
	switch ( next ) {
	case STAGE_STREET:
		if ( _stage != STAGE_RYUGU ) {
			//竜宮から戻ってくるときは亀を出さない。
			office->add( RockEventCharacterPtr( new RockEventTurtle( Vector( 3610, 320, -210 ) ) ) );
		}
		office->add( RockEventCharacterPtr( new RockEventObaba( Vector( 7200, 600, -110 ) ) ) );
		office->add( RockEventCharacterPtr( new RockEventMiko( Vector( 3910, 320, -310 ) ) ) );
		break;
	case STAGE_CAVE:
		break;
	case STAGE_RYUGU:
		office->add( RockEventCharacterPtr( new RockEventTurtle( Vector( 900, 30, 0 ) ) ) );
		office->add( RockEventCharacterPtr( new RockEventOtohime( Vector( -460, 30, 0 ) ) ) );
		break;
	}
}

void RockMapStreet::resetFamilyPos( STAGE next ) {
	RockFamilyPtr family = RockFamily::getTask( );
	switch ( next ) {
	case STAGE_STREET:
		if ( _stage == STAGE_RYUGU ) {
			//亀の位置に戻る
			family->resetPos( Vector( 3610, 320, -210 ) );
		}
		if ( _stage != STAGE_RYUGU ) {
			//初期位置
			family->resetPos( Vector( 0, 10, -500 ) );
		}
		break;
	case STAGE_CAVE:
		family->resetPos( Vector( 0, 10, 0 ) );
		break;
	case STAGE_RYUGU:
		family->resetPos( Vector( 800, 5, 0 ) );
		break;
	}
}

bool RockMapStreet::isInActivePlayer( ) {
	RockFamilyPtr family = RockFamily::getTask( );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		if ( family->getPlayer( i )->isActive( ) ) {
			return true;
		}
	}

	return false;
}