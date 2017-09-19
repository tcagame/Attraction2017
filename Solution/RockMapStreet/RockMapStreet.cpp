#include "RockMapStreet.h"
#include "RockMapStreetDrawer.h"
#include "RockCamera.h"
#include "Status.h"
#include "MessageSender.h"
#include "Client.h"
#include "Sound.h"
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
#include "RockPop.h"
#include "RockMilitary.h"
#include "RockEnemyGhost.h"
#include "RockEnemyRedBard.h"
#include "RockEnemyWaterGhost.h"
#include "RockEnemyFaceAndHand.h"
#include "RockEnemyBat.h"
#include "RockEnemyKimono.h"
#include "RockEnemyCloud.h"
#include "RockEnemySkeleton.h"
#include "RockEnemyStone.h"
#include "RockEnemyLittleRedDaemon.h"
#include "RockEnemyBossRedDaemon.h"

PTR( RockEnemyBossRedDaemon );

const int REMOVE_CAVE_TIME = 500;
const int DROP_TIMING = 1800;

RockMapStreet::RockMapStreet( StatusPtr status ) :
_virtue_pop( false ),
_status( status ) {
}

RockMapStreet::~RockMapStreet( ) {
}

void RockMapStreet::initialize( ) {
	Client::getTask( )->update( );
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
	Sound::getTask( )->stopBGM( );
	bool active = false;
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		RockPlayerPtr player = family->getPlayer( i );
		if ( !player->isActive( ) ) {
			continue;
		}
		active = true;
		{//洞窟へ行くとSTAGE_CAVEへ移動
			//double length = ( Vector( 17675, -1105, 6123 ) - player->getPos( ) ).getLength( );
			//Debug用鳥居ワープ
			double length = ( Vector( -173, 3, -520 ) - player->getPos( ) ).getLength( );

			if ( length < 100 ) {
				loadStage( STAGE_CAVE );
				RockFamily::getTask( )->resetPos( Vector( -1679, 0, -185 ) );
				Sound::getTask( )->playBGM( "yokai_music_04.wav" );
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
						Sound::getTask( )->playBGM( "yokai_music_06.wav" );
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
		RockArmoury::getTask( )->clearShot( );
	}
}

void RockMapStreet::updateCave( ) {
	RockFamilyPtr family = RockFamily::getTask( );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		RockPlayerPtr player = family->getPlayer( i );
		if ( !player->isActive( ) ) {
			continue;
		}
	}

	RockMilitaryPtr military = RockMilitary::getTask( );
	std::list< RockEnemyPtr > enemies = military->getEnemyList( );
	std::list< RockEnemyPtr >::iterator ite = enemies.begin( );
	bool load = true;
	if ( enemies.size( ) > 0 ) {
		load = false;
	}
	while ( ite != enemies.end( ) ) {
		RockEnemyBossRedDaemonPtr redDaemon = std::dynamic_pointer_cast< RockEnemyBossRedDaemon >( *ite );
		if ( redDaemon ) {
			load = false;
			break;
		}
		ite++;
	}

	if ( load ) {
		for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
			int value = 50000;
			 MessageSender::getTask( )->sendMessage( i, Message::COMMAND_MONEY, &value );
		}
		Sound::getTask( )->playSE( "yokai_se_32.wav" );
		loadStage( STAGE_STREET );
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
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyStone      ( Vector(  800,  60, -520 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector(  850,  60, -520 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyWaterGhost ( Vector( 3800, 320, -530 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyWaterGhost ( Vector( 4100, 320, -700 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyWaterGhost ( Vector( 4700, 320, -680 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyCloud      ( Vector( 4500, 330, -650 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyCloud      ( Vector( 4900, 330, -650 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyBat        ( Vector( 2000, 190, -600 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyKimono     ( Vector( 7200, 600, -110 ) ) ), true ) ) );
		break;
	case STAGE_CAVE:
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyBossRedDaemon  ( Vector( 20, 20,   0 ) ) ), true ) ) );
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
			storage->addItem( RockItemPtr( new RockItemMoney( Vector( i * INTERVAL, 200, -500 - i * 10 ), 500 ) ) );
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
	{
		if ( _stage != STAGE_RYUGU ) {
			//竜宮から戻ってくるときは亀を出さない。
			office->add( RockEventCharacterPtr( new RockEventTurtle( Vector( 3610, 335, -210 ) ) ) );
		}
		bool genarate_miko = true;
		for ( int i = 0; i < ROCK_PLAYER_NUM; i++  ) {
			if ( _status->getPlayer( i ).item & ITEM_HEART ) {
				genarate_miko = false;
				break;//forを抜ける
			}
		}
		if ( genarate_miko ) {
			office->add( RockEventCharacterPtr( new RockEventMiko( Vector( 3910, 350, -310 ), _status ) ) );
		}
	}
		office->add( RockEventCharacterPtr( new RockEventObaba( Vector( 7200, 600, -110 ) ) ) );
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