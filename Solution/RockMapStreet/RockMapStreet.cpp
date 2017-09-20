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
#include "RockItemDango.h"
#include "RockItemEnhancePower.h"
#include "RockItemEnhanceCharge.h"
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
#include "RockEnemySmallFrog.h"
#include "RockEnemyChivil.h"
#include "RockEnemyMoth.h"
#include "RockEnemyLittleRedDaemon.h"
#include "RockEnemyBossRedDaemon.h"

PTR( RockEnemyBossRedDaemon );

const int REMOVE_CAVE_TIME = 500;
const int DROP_TIMING = 1800;
const Vector OBABA_POS( 7200, 750, -110 );

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
			double length = ( Vector( 17675, -1105, 6123 ) - player->getPos( ) ).getLength( );
			//Debug用鳥居ワープ
			//double length = ( Vector( -173, 3, -520 ) - player->getPos( ) ).getLength( );

			if ( length < 100 ) {
				loadStage( STAGE_CAVE );
				RockFamily::getTask( )->resetPos( Vector( 16347, -1104, 5888 ) );
				Sound::getTask( )->playBGM( "yokai_music_04.wav" );
			}
		}
		//{//debug
		//	double length1 = ( Vector( -173, 3, -520 ) - player->getPos( ) ).getLength( );
		//	if ( length1 < 100 ) {
		//		//loadStage( STAGE_CAVE );
		//		RockFamily::getTask( )->resetPos( Vector( 17575, -1105, 6023 ) );
		//		Sound::getTask( )->playBGM( "yokai_music_04.wav" );
		//	}
		//}
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
	resetFamilyPos( next );
	genarateEnemies( next );
	genarateEventCharacters( next );
	genarateStorage( next );
	_drawer.reset( new RockMapStreetDrawer( next ) );
	_stage = next;
	_virtue_pop = false;
}



void RockMapStreet::genarateEnemies( STAGE next ) {
	RockMilitaryPtr military = RockMilitary::getTask( );
	military->clean( );
	switch ( next ) {
	case STAGE_STREET:
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySmallFrog  ( Vector(   2703,   303,  -423 ) ) ), true ) ) );
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySmallFrog	 ( Vector(   2743,   353,  -653 ) ) ), true ) ) );
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySmallFrog  ( Vector(   2603,   303,  -403 ) ) ), true ) ) );
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySmallFrog  ( Vector(   2503,   300   -443 ) ) ), true ) ) );
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySmallFrog  ( Vector(   2103,   253,  -423 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyGhost  ( Vector(   2303,   253,  -503 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyGhost  ( Vector(   2203,   253,  -453 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyGhost  ( Vector(   2303,   265,  -603 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector(  15350,   -850,  1400 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector(  16500,   -850,   300 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector(  16000,   -850,   100 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector(  15500,   -850,   100 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector(  7200, 50, -310 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector(  7200, 50, -510 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector(  7200, 50, -610 ) ) ), true ) ) );
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector(  4300,   -250,  -520 ) ) ), true ) ) );
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector(  3400,   -568, -3120 ) ) ), true ) ) );//坂の折り返し
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyGhost   ( Vector(  3100,   -658, -2920 ) ) ), true ) ) );//坂の折り返し
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyGhost   ( Vector(  3250,   -658, -3220 ) ) ), true ) ) );//坂の折り返し
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyGhost   ( Vector(  3400,   -658, -3120 ) ) ), true ) ) );//坂の折り返し
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector(  5110,   -850, -3120 ) ) ), true ) ) );//下の坂の中心
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector(  7400,   -900, -3120 ) ) ), true ) ) );//海の手前
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector(  9090,  -1350, -2840 ) ) ), true ) ) );//海の最初
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector(  9950,  -1380, -2843 ) ) ), true ) ) );//海の最初と中心の間
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector( 11000,  -1380, -2553 ) ) ), true ) ) );//海の中心
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyWaterGhost ( Vector(11000, -1380, -2553) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyWaterGhost ( Vector(12220, -1380, -2553) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyWaterGhost ( Vector(13360, -1380, -2003) ) ), true ) ) );
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector( 12220,  -1380, -2553 ) ) ), true ) ) );//海の中心と最後の間
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector( 13360,  -1380, -2003 ) ) ), true ) ) );//海の最後
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector( 15600,  -1380, -2843 ) ) ), true ) ) );//海の隅っこ下
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector( 13080,  -1380,     0 ) ) ), true ) ) );//海の隅っこ上
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector( 16500,   -850,     0 ) ) ), true ) ) );//橋手前　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector( 15080,   -850,  3412 ) ) ), true ) ) );//洞窟手前
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector( 15350,   -850,  1700 ) ) ), true ) ) );//橋の上
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyRedBard ( Vector(  3400,    420,  -630 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyRedBard ( Vector(  3400,    420,  -530 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyRedBard ( Vector(  3300,    420,  -760 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyWaterGhost ( Vector(  3800,    320,  -530 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyWaterGhost ( Vector(  4100,    320,  -700 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyWaterGhost ( Vector(  5300,    320,  -780 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyWaterGhost ( Vector(  4700,    320,  -680 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyWaterGhost ( Vector(  4400,    320,  -600 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyWaterGhost ( Vector(  3700,    320,  -800 ) ) ), true ) ) );
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyCloud      ( Vector(  4500,    330,  -650 ) ) ), true ) ) );
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyCloud      ( Vector(  4900,    330,  -650 ) ) ), true ) ) );
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyBat        ( Vector(  2000,    190,  -600 ) ) ), true ) ) );
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyKimono     ( Vector(   950,     60,  -510 ) ) ), true ) ) );
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyFaceAndHand( Vector(  6000,    360,  -620 ) ) ), true ) ) );
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyGhost		 ( Vector(   900,     60,  -520 ) ) ), true ) ) );
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySmallFrog	 ( Vector(  7250,    600, -1020 ) ) ), true ) ) );
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyChivil	 ( Vector(  7200,     60, -3020 ) ) ), true ) ) );
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyMoth		 ( Vector(  7250,    500, -2020 ) ) ), true ) ) );
		break;
	case STAGE_CAVE:
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyBossRedDaemon  ( Vector( 17675, -1105, 6123 ) ) ), true ) ) );
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
		//const int INTERVAL = 200;
		//for ( int i = 0; i < 30; i++ ) {
		//	storage->addItem( RockItemPtr( new RockItemMoney( Vector( i * INTERVAL, 200, -500 - i * 10 ), 500 ) ) );
		//}
		storage->addAlter( RockAlterPtr( new RockAlter( Vector( 300, 0, -300 ), Vector( 0, 0, -1 ) ) ) );
		//ショップアイテム
		storage->addShopItem( RockItemPtr( new RockItemEnhancePower ( Vector( OBABA_POS.x + 50, OBABA_POS.y, OBABA_POS.z - 50 ) ) ) );
		storage->addShopItem( RockItemPtr( new RockItemDango        ( Vector( OBABA_POS.x, OBABA_POS.y, OBABA_POS.z - 50 ) ) ) );
		storage->addShopItem( RockItemPtr( new RockItemEnhanceCharge( Vector( OBABA_POS.x - 50, OBABA_POS.y, OBABA_POS.z - 50 ) ) ) );
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
		office->add( RockEventCharacterPtr( new RockEventObaba( OBABA_POS ) ) );
		break;
	case STAGE_CAVE:
		break;
	case STAGE_RYUGU:
		office->add( RockEventCharacterPtr( new RockEventTurtle( Vector( 750, 10, 120 ) ) ) );
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
			family->resetPos( Vector( 3610, 320, -550 ) );
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