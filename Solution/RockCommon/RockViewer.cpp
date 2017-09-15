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
#include "RockItemBubble.h"
#include "RockShot.h"
#include "RockImpact.h"
#include "RockCasket.h"
#include "Effect.h"
#include "RockAlter.h"
#include "RockAncestors.h"
#include "Movie.h"
#include "RockTheater.h"
#include "RockBubble.h"
#include "RockOffice.h"
#include "RockEventCharacter.h"
#include "RockShadow.h"
#include "ModelMDL.h"

const int DRAW_UI_Y = 512;
const int HP_GRAPH_HEIGHT = 16;
const int HP_GRAPH_WIDTH = 8;
const int MONEY_GRAPH_HEIGHT = 16;
const int MONEY_GRAPH_WIDTH = 15;
const int MONEY_Y = DRAW_UI_Y + 125;
const int ITEM_GRAPH_SIZE = 64;
const int ITEM_Y = DRAW_UI_Y + 160;
const int ITEM_DRAW_SIZE = 32;
const int CONTINUE_GRAPH_SIZE = 32;
const int CONTINUE_Y = DRAW_UI_Y + 126;
const int CONTINUE_DRAW_SIZE = CONTINUE_GRAPH_SIZE / 2;
const int CONTINUE_X_NUM = 13;
const int VIRTUE_GRAPH_WIDTH = 32;

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
	//要差し替え
	_dummy_ui = drawer->createImage( "UI/item.png" );

	//本番データ
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {		
		char filename[ 256 ];
		sprintf_s( filename, "UI/breast%d.png", i + 1 );
		ImagePtr image = drawer->createImage( filename );
		_breasts.push_back( image );
	}
	
	_image_frame.push_back( drawer->createImage( "UI/tarosuke_status_window.png" ) );
	_image_frame.push_back( drawer->createImage( "UI/garisuke_status_window.png" ) );
	_image_frame.push_back( drawer->createImage( "UI/tarojiro_status_window.png" ) );
	_image_frame.push_back( drawer->createImage( "UI/taromi_status_window.png" ) );
	//POWER
	_power.push_back( drawer->createImage( "UI/ui_power_bit01.png" ) );
	_power.push_back( drawer->createImage( "UI/ui_power_bit02.png" ) );
	_power.push_back( drawer->createImage( "UI/ui_power_bit03.png" ) );
	_power.push_back( drawer->createImage( "UI/ui_power_bit04.png" ) );
	_power.push_back( drawer->createImage( "UI/ui_power_bit05.png" ) );
	_power.push_back( drawer->createImage( "UI/ui_power_bit06.png" ) );
	_power.push_back( drawer->createImage( "UI/ui_power_bit07.png" ) );
	//ITEM
	_items.push_back( drawer->createImage( "UI/ui_item_dango.png"  ) );
	_items.push_back( drawer->createImage( "UI/ui_item_heart.png"  ) );
	_items.push_back( drawer->createImage( "UI/ui_item_shot.png"   ) );
	_items.push_back( drawer->createImage( "UI/ui_item_charge.png" ) );
	_items.push_back( drawer->createImage( "UI/ui_item_fire.png"   ) );
	_items.push_back( drawer->createImage( "UI/ui_item_rock.png"   ) );
	_items.push_back( drawer->createImage( "UI/ui_item_tree.png"   ) );
	_virtue = drawer->createImage( "UI/ui_item_virtue.png" );
	//数字
	_money_num = drawer->createImage( "UI/ui_money_number.png" );
	_virtue_num = drawer->createImage( "UI/ui_virtue_number.png" );
}

void RockViewer::update( ) {
	DrawerPtr drawer = Drawer::getTask( );
	drawer->waitForSync( );
	drawer->flip( );
	drawMap( );
	drawShadow( );
	drawEnemy( );
	drawPlayer( );
	drawAncestors( );
	drawEventCharacter( );
	//drawShot( );
	drawItem( );
	drawAlter( );
	drawCasket( );
	drawCleannessMap( );
	drawBubbles( );
	Effect::getTask( )->drawEffect( );
	drawUI( );
	drawResult( );
}

void RockViewer::drawMap( ) const {
	std::vector< ModelMV1Ptr > back_ground_models = RockMap::getTask( )->getBackGroundModels( );
	int back_ground_size = ( int )back_ground_models.size( );
	for ( int i = 0; i < back_ground_size; i++ ) {
		back_ground_models[ i ]->draw( );
	}

	std::vector< ModelMV1Ptr > models = RockMap::getTask( )->getModels( );
	int size = ( int )models.size( );
	for ( int i = 0; i < size; i++ ) {
		models[ i ]->draw( );
	}
}

void RockViewer::drawCleannessMap( ) const {
	std::vector< ModelMV1Ptr > models = RockMap::getTask( )->getCleannessModels( );
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
	RockClientInfoPtr info = RockClientInfo::getTask( );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		if ( !info->isActiveState( _status->getPlayer( i ).area ) ) {
			continue;
		}
		ModelMV1Ptr model = family->getPlayer( i )->getModel( );
		model->draw( );
	}
}

void RockViewer::drawBubbles( ) const {
	//player
	RockFamilyPtr family( RockFamily::getTask( ) );
	RockClientInfoPtr info = RockClientInfo::getTask( );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		if ( !info->isActiveState( _status->getPlayer( i ).area ) ) {
			continue;
		}
		RockBubblePtr bubble = family->getBubble( i );
		if ( bubble->isActive( ) ) {
			ModelMV1Ptr model = bubble->getModel( );
			model->draw( );
		}
	}

	//item
	RockStoragePtr storage( RockStorage::getTask( ) );
	std::list< RockItemBubblePtr > items = storage->getBubbles( );
	std::list< RockItemBubblePtr >::const_iterator ite = items.begin( );
	while ( ite != items.end( ) ) {
		RockItemBubblePtr item = *ite;
		if ( !item ) {
			ite++;
			continue;
		}
		ModelMV1Ptr model = item->getModel( );
		model->draw( );
		ite++;
	}
}


void RockViewer::drawAncestors( ) const {
	RockFamilyPtr family( RockFamily::getTask( ) );
	RockClientInfoPtr info = RockClientInfo::getTask( );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		RockAncestorsPtr ancestors = family->getAncestors( i );
		if ( !info->isActiveState( _status->getPlayer( i ).area ) ||
			 !ancestors->isActive( ) ) {
			continue;
		}
		ModelMV1Ptr model = ancestors->getModel( );
		model->draw( );
	}
}

void RockViewer::drawEventCharacter( ) const {
	RockOfficePtr office( RockOffice::getTask( ) );

	if ( !office ) {
		return;
	}

	std::list< RockEventCharacterPtr > event_characters = office->getEventCharacters( );
	std::list< RockEventCharacterPtr >::const_iterator ite = event_characters.begin( );
	while ( ite != event_characters.end( ) ) {
		RockEventCharacterPtr chara = *ite;
		if ( !chara ) {
			ite++;
			continue;
		}

		ModelMV1Ptr model = chara->getModel( );
		model->draw( );
		ite++;
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

void  RockViewer::drawShadow( ) const {
	RockShadowPtr shadow( RockShadow::getTask( ) );
	if ( !shadow ) {
		return;
	}
	int size = shadow->getSetNum( );
	for ( int i = 0; i < size; i++ ) {
		ModelMDLPtr model = shadow->getModel( i );
		model->draw( );
	}
	shadow->reset( );
}

void RockViewer::drawUI( ) const {
	RockFamilyPtr family( RockFamily::getTask( ) );
	RockClientInfoPtr info = RockClientInfo::getTask( );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		if ( !info->isActiveState( _status->getPlayer( i ).area ) ||
			 _status->getPlayer( i ).area == AREA_RESULT ) {
			continue;
		}
		if ( family->getPlayer( i )->isBubble( ) &&
			 info->isActiveState( AREA_ENTRY ) ) {
			_breasts[ i ]->setRect( 0, 0, 320, 360 );
			_breasts[ i ]->setPos( i * ( SCREEN_WIDTH / 4 ), SCREEN_HEIGHT - 256, ( i + 1 ) * ( SCREEN_WIDTH / 4 ), SCREEN_HEIGHT );
			_breasts[ i ]->draw( );
			continue;
		}
		int player_status_pos = i * ( SCREEN_WIDTH / 4 );
		_image_frame[ i ]->setPos( player_status_pos, DRAW_UI_Y );
		_image_frame[ i ]->draw( );

		{//(POWER)
			int power = _status->getPlayer( i ).power;
			for ( int j = 0; j < power; j++ ) {
				int sx = player_status_pos + 165 + j * 8;
				int sy = DRAW_UI_Y + 77;
				int dot = j / 2;
				if ( dot > 6 ) {
					dot = 6;
				}
				_power[ dot ]->setPos( sx, sy );
				_power[ dot ]->draw( );
			}
		}
		
		{//(MONEY)
			int money = _status->getPlayer( i ).money;
			int digit = money == 0;
			while( money > 0 ) {
				digit++;
				money /= 10;
			}
			for ( int j = 0; j < digit; j++ ) {
				int num = _status->getPlayer( i ).money % (int)pow( 10.0, (double)j + 1 );
				num /= (int)pow( 10.0, (double)j );
				_money_num->setRect( MONEY_GRAPH_WIDTH * num, 0, MONEY_GRAPH_WIDTH, MONEY_GRAPH_HEIGHT );
				int sx = player_status_pos + -j * MONEY_GRAPH_WIDTH + 275;
				_money_num->setPos( sx, MONEY_Y, sx + MONEY_GRAPH_WIDTH, MONEY_Y + 14 );
				_money_num->draw( );
			}
		}

		{//(ITEM)
			unsigned int item = _status->getPlayer( i ).item;
			for ( int j = 0; j < MAX_ITEM_NUM; j++ ) {
				unsigned int check = 1 << j;
				if ( item & check ) {
					int sx = player_status_pos + 10 + ITEM_DRAW_SIZE * j - ( j != 0 ) * 10;
					int sy = ITEM_Y;
					_items[ j ]->setPos( sx, sy, sx + ITEM_DRAW_SIZE, sy + ITEM_DRAW_SIZE );
					_items[ j ]->draw( );
				}
			}
		}

		{// 徳表示
			_virtue->setPos( player_status_pos + 224, ITEM_Y );
			_virtue->draw( );
			int virtue = _status->getPlayer( i ).toku;
		
			int sx = player_status_pos + 280;
			int sy = ITEM_Y + 8;
			int digit = virtue == 0;
			while( virtue > 0 ) {
				digit++;
				virtue /= 10;
			}
			for ( int j = 0; j < digit; j++ ) {
				int num = _status->getPlayer( i ).toku % (int)pow( 10.0, (double)j + 1 );
				num /= (int)pow( 10.0, (double)j );
				_virtue_num->setRect( VIRTUE_GRAPH_WIDTH * num, 0, VIRTUE_GRAPH_WIDTH, VIRTUE_GRAPH_WIDTH );
				_virtue_num->setPos( sx, sy, sx + 18, sy + 18 );
				_virtue_num->draw( );
				sx -= MONEY_GRAPH_WIDTH;
			}
		}
		{//コンティニュー
			unsigned int continue_num = _status->getPlayer( i ).continue_num;
			for ( int j = 0; j < (int)continue_num; j++ ) {
				_dummy_ui->setRect( CONTINUE_GRAPH_SIZE * 2, CONTINUE_GRAPH_SIZE * 4, CONTINUE_GRAPH_SIZE, CONTINUE_GRAPH_SIZE );
				int sx = player_status_pos + 105 - ( CONTINUE_DRAW_SIZE / 2 ) * ( j % CONTINUE_X_NUM );
				int sy = CONTINUE_Y - ( j / CONTINUE_X_NUM ) * CONTINUE_DRAW_SIZE;
				_dummy_ui->setPos( sx, sy, sx + CONTINUE_DRAW_SIZE, sy + CONTINUE_DRAW_SIZE );
				_dummy_ui->draw( );
			}
		}
	}
}

void RockViewer::drawResult( ) const {
	RockTheaterPtr theater = RockTheater::getTask( );
	if ( !theater ) {
		return;
	}
	MoviePtr movie = theater->getMovie( );
	if ( movie->isPlay( ) ) {
		movie->draw( );
	} 
	ImagePtr image = theater->getImage( );
	if ( image ) {
		image->draw( );
	}
}
