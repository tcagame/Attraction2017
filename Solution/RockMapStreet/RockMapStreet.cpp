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

#include "Drawer.h"

PTR( RockEnemyBossRedDaemon );
const int CAVE_REWORD = 50000;
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
		if ( !active ) {
			RockArmoury::getTask( )->clearShot( );
		}
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
		RockFamilyPtr family = RockFamily::getTask( );
		for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
			RockPlayerPtr player = family->getPlayer( i );
			if ( !player->isActive( ) ) {
				continue;
			}
			int value = CAVE_REWORD;
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
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySmallFrog  ( Vector(  1421,   10,  -823 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySmallFrog  ( Vector(  1421,   10,  -653 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySmallFrog	 ( Vector(  1421,   10,  -568 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySmallFrog  ( Vector(  1221,   10,  -823 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySmallFrog  ( Vector(  1221,   10,  -653 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySmallFrog  ( Vector(  1221,   10,  -568 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySmallFrog  ( Vector(  1021,   10,  -823 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySmallFrog  ( Vector(  1021,   10,  -653 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySmallFrog  ( Vector(  1021,   10,  -568 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyGhost      ( Vector(  2303,  253,  -503 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyGhost      ( Vector(  2203,  253,  -453 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyGhost      ( Vector(  2403,  265,  -650 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyGhost      ( Vector(  2303,  265,  -603 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector( 15350, -850,  1400 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector( 16500, -850,   300 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector( 16000, -850,   100 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector( 15500, -850,   100 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector(  7200,  -70,  -310 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector(  7200,  -70,  -510 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector(  7200,  -70,  -910 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector(  7400,  -70,  -910 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector(  7200,  -70,  -1010 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector(  7400,  -70,  -1010 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector(  7200,  -70,  -1410 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector(  7200,  -70,  -1510 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector( 15390,   -1100,  1500 ) ) ), true ) ) );//橋の上
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector( 15690,   -1100,  1400 ) ) ), true ) ) );//橋の上
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector( 15390,   -1100,  1500 ) ) ), true ) ) );//橋の上
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector( 15390,   -1100,  1500 ) ) ), true ) ) );//橋の上
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector(  3400,   -568, -3120 ) ) ), true ) ) );//坂の折り返し
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector(  4300,   -250,  -520 ) ) ), true ) ) );
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector(  5110,   -850, -3120 ) ) ), true ) ) );//下の坂の中心
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector(  7400,   -900, -3120 ) ) ), true ) ) );//海の手前
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector(  9090,  -1350, -2840 ) ) ), true ) ) );//海の最初
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector(  9950,  -1380, -2843 ) ) ), true ) ) );//海の最初と中心の間
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector( 11000,  -1380, -2553 ) ) ), true ) ) );//海の中心
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector( 12220,  -1380, -2553 ) ) ), true ) ) );//海の中心と最後の間
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector( 13360,  -1380, -2003 ) ) ), true ) ) );//海の最後
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector( 15600,  -1380, -2843 ) ) ), true ) ) );//海の隅っこ下
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector( 13080,  -1380,     0 ) ) ), true ) ) );//海の隅っこ上
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySkeleton   ( Vector( 16500,   -850,     0 ) ) ), true ) ) );//橋手前　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyCloud      ( Vector(  5600,    -60,  -2120 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyCloud      ( Vector(  5300,    -120,  -2220 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyCloud      ( Vector(  5000,    -200,  -2120 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyCloud      ( Vector(  5000,    -230,  -2220 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyCloud      ( Vector(  4800,    -260,  -2120 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyGhost   ( Vector(  3100,   -658, -2920 ) ) ), true ) ) );//坂の折り返し
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyGhost   ( Vector(  3250,   -658, -3220 ) ) ), true ) ) );//坂の折り返し
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyGhost   ( Vector(  3120,   -658, -3120 ) ) ), true ) ) );//坂の折り返し
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyGhost   ( Vector(  3400,   -658, -3120 ) ) ), true ) ) );//坂の折り返し
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyChivil   ( Vector( 15080,   -1100,  3912 ) ) ), true ) ) );//洞窟手前
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyChivil   ( Vector( 15580,   -1100,  3812 ) ) ), true ) ) );//洞窟手前
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyChivil   ( Vector( 16080,   -1100,  3852 ) ) ), true ) ) );//洞窟手前
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyChivil   ( Vector( 17680,   -1100,  5542 ) ) ), true ) ) );//洞窟の鳥居近く
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyChivil   ( Vector( 17680,   -1100,  5742 ) ) ), true ) ) );//洞窟の鳥居近く
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyChivil   ( Vector( 17680,   -1100,  5942 ) ) ), true ) ) );//洞窟の鳥居近く
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyRedBard ( Vector(  3400,   450,  -630 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyRedBard ( Vector(  3400,   450,  -530 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyRedBard ( Vector(  3300,   450,  -760 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyRedBard ( Vector(  3800,   440,  -630 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyRedBard ( Vector(  3800,   440,  -530 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyRedBard ( Vector(  3700,   440,  -760 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyRedBard ( Vector(  4200,   440,  -630 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyRedBard ( Vector(  4200,   440,  -530 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyRedBard ( Vector(  4100,   440,  -760 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyRedBard ( Vector(  4600,   440,  -630 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyRedBard ( Vector(  4600,   440,  -530 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyRedBard ( Vector(  4500,   440,  -760 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyRedBard ( Vector(  5000,   440,  -630 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyRedBard ( Vector(  5000,   440,  -530 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyRedBard ( Vector(  4900,   440,  -760 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyRedBard ( Vector(  7050,  -900, -3050 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyRedBard ( Vector(  7100,  -900, -2900 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyRedBard ( Vector(  7100,  -900, -3120 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyRedBard ( Vector( 11900, -1300, -2540 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyRedBard ( Vector( 11800, -1300, -2400 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyRedBard ( Vector( 11700, -1300, -2300 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyRedBard ( Vector( 11800, -1300, -2300 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyWaterGhost ( Vector(  4400,   320,  -600 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyWaterGhost ( Vector(  3800,   320,  -530 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyWaterGhost ( Vector(  4100,   320,  -700 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyWaterGhost ( Vector(  5300,   320,  -780 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyWaterGhost ( Vector(  4700,   320,  -680 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyWaterGhost ( Vector(  4400,   320,  -600 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyWaterGhost ( Vector(  3700,   320,  -800 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyWaterGhost ( Vector(  8600, -1350,  3200 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyWaterGhost ( Vector(  8639, -1350,  3160 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyWaterGhost ( Vector(  8900, -1350, -3303) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyWaterGhost ( Vector(  9520, -1350, -3303) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyWaterGhost ( Vector( 10360, -1350, -3103) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyWaterGhost ( Vector( 10360, -1350, -2903) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyWaterGhost ( Vector( 10360, -1350, -3003) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyWaterGhost ( Vector( 11760, -1350, -2803) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyWaterGhost ( Vector( 12360, -1350, -2603) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyWaterGhost ( Vector( 13360, -1350, -2303) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyWaterGhost ( Vector( 12360, -1350, -2203) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyWaterGhost ( Vector( 13160, -1350, -1903) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyWaterGhost ( Vector( 13190, -1350, -1713) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyWaterGhost ( Vector( 13390, -1350, -1493) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyWaterGhost ( Vector( 13760, -1350, -1503) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyWaterGhost ( Vector( 13760, -1350, -1603) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyBat        ( Vector(  6700,  -950,  -3000 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyBat        ( Vector(  6700,  -950,  -2900 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyBat        ( Vector(  6550,  -950,  -2900 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyBat        ( Vector(  6550,  -950,  -3000 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyBat        ( Vector(  6350,  -950,  -3000 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyBat        ( Vector(  6350,  -950,  -3100 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyBat        ( Vector(  6000,  -950,  -3100 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyBat        ( Vector(  6000,  -950,  -3100 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyBat        ( Vector(  6000,  -950,  -3000 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyBat        ( Vector(  5700,  -950,  -3000 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyBat        ( Vector(  5700,  -950,  -3100 ) ) ), true ) ) );
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyKimono     ( Vector(   950,     60,  -510 ) ) ), true ) ) );
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyFaceAndHand( Vector(  6000,    360,  -620 ) ) ), true ) ) );
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyGhost		( Vector(   900,     60,  -520 ) ) ), true ) ) );
		//military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemySmallFrog	( Vector(  7250,    600, -1020 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyFaceAndHand	( Vector(  9230,    -1350, -3420 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyFaceAndHand	( Vector(  9890,    -1350, -3220 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyFaceAndHand	( Vector(  10890,    -1350, -2620 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyFaceAndHand	( Vector(  10890,    -1350, -2620 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyFaceAndHand	( Vector(  14850,    -1050, -520 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyFaceAndHand	( Vector(  15250,    -1100, -560 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyFaceAndHand	( Vector(  15050,    -1020, -530 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyFaceAndHand	( Vector(  16050,    -1060, -430 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyFaceAndHand	( Vector(  17050,    -1060, -230 ) ) ), true ) ) );
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyFaceAndHand	( Vector(  16050,    -1060, -330 ) ) ), true ) ) );
		break;
	case STAGE_CAVE:
		military->addPop( RockPopPtr( new RockPop( RockEnemyPtr( new RockEnemyBossRedDaemon  ( Vector( 17733, -1104, 5960 ) ) ), true ) ) );
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
		storage->addAlter( RockAlterPtr( new RockAlter( Vector( 300, 0, -300 ), Vector( 0, 0, -1 ) ) ) );
		//ショップアイテム
		storage->addShopItem( RockItemPtr( new RockItemEnhancePower ( Vector( OBABA_POS.x + 50, OBABA_POS.y, OBABA_POS.z - 50 ) ) ) );
		storage->addShopItem( RockItemPtr( new RockItemDango        ( Vector( OBABA_POS.x, OBABA_POS.y, OBABA_POS.z - 50 ) ) ) );
		storage->addShopItem( RockItemPtr( new RockItemEnhanceCharge( Vector( OBABA_POS.x - 50, OBABA_POS.y, OBABA_POS.z - 50 ) ) ) );
		//徳まみれ
		storage->addItem( RockItemPtr( new RockItemToku( Vector( 660,     10,   -623 ) ) ) );
		storage->addItem( RockItemPtr( new RockItemToku( Vector( 2813,   343,   -615 ) ) ) );
		storage->addItem( RockItemPtr( new RockItemToku( Vector( 7206,   -70,   -774 ) ) ) );
		storage->addItem( RockItemPtr( new RockItemToku( Vector( 6903,   -70,  -1623 ) ) ) );
		storage->addItem( RockItemPtr( new RockItemToku( Vector( 5300,   -230, -2165 ) ) ) );
		storage->addItem( RockItemPtr( new RockItemToku( Vector( 3463,   -560, -2311 ) ) ) );
		storage->addItem( RockItemPtr( new RockItemToku( Vector( 4544,   -820, -3122 ) ) ) );
		storage->addItem( RockItemPtr( new RockItemToku( Vector( 6616,  -1000, -3056 ) ) ) );
		storage->addItem( RockItemPtr( new RockItemToku( Vector( 8401,  -1356, -3056 ) ) ) );
		storage->addItem( RockItemPtr( new RockItemToku( Vector( 13963, -1290, -1218 ) ) ) );
		storage->addItem( RockItemPtr( new RockItemToku( Vector( 15045, -1095,  -693 ) ) ) );
		storage->addItem( RockItemPtr( new RockItemToku( Vector( 16224, -1095,   267 ) ) ) );
		storage->addItem( RockItemPtr( new RockItemToku( Vector( 15664, -1081,  1113 ) ) ) );
		storage->addItem( RockItemPtr( new RockItemToku( Vector( 15260, -1079,  1649 ) ) ) );
		storage->addItem( RockItemPtr( new RockItemToku( Vector( 14827, -1078,  2190 ) ) ) );
		storage->addItem( RockItemPtr( new RockItemToku( Vector( 14587, -1095,  2830 ) ) ) );
		storage->addItem( RockItemPtr( new RockItemToku( Vector( 17363, -1095,  4694 ) ) ) );
		storage->addItem( RockItemPtr( new RockItemToku( Vector( 17722, -1095,  5772 ) ) ) );
		storage->addItem( RockItemPtr( new RockItemToku( Vector( 17692, -1095,  5772 ) ) ) );
		storage->addItem( RockItemPtr( new RockItemToku( Vector( 17662, -1095,  5772 ) ) ) );
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