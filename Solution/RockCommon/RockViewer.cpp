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
#include "RockBubble.h"
#include "RockOffice.h"
#include "RockEventCharacter.h"
#include "RockShadow.h"
#include "ModelMDL.h"

const int DRAW_UI_Y = 512;
const int HP_GRAPH_HEIGHT = 16;
const int HP_GRAPH_WIDTH = 8;
const int MONEY_GRAPH_HEIGHT = 16;
const int MONEY_GRAPH_WIDTH = 12;
const int MONEY_Y = DRAW_UI_Y + 102;
const int ITEM_GRAPH_SIZE = 64;
const int ITEM_Y = DRAW_UI_Y + 158;
const int ITEM_DRAW_SIZE = 24;
const int CONTINUE_GRAPH_SIZE = 32;
const int CONTINUE_Y = DRAW_UI_Y + 126;
const int CONTINUE_DRAW_SIZE = CONTINUE_GRAPH_SIZE / 2;
const int CONTINUE_X_NUM = 13;

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
	_image_frame = drawer->createImage( "UI/status_plate.png" );
	_status_ui = drawer->createImage( "UI/ui.png" );
	_status_num = drawer->createImage( "UI/ui_num.png" );
	_dummy_ui = drawer->createImage( "UI/item.png" );

	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {		
		char filename[ 256 ];
		sprintf_s( filename, "UI/breast%d.png", i + 1 );
		ImagePtr image = drawer->createImage( filename );
		_breasts.push_back( image );
	}
}

void RockViewer::update( ) {
	DrawerPtr drawer = Drawer::getTask( );
	drawer->waitForSync( );
	drawer->flip( );
	drawMap( );
	drawShadow( );
	drawEnemy( );
	drawPlayer( );
	drawBubble( );
	drawCleannessMap( );
	drawAncestors( );
	drawEventCharacter( );
	//drawShot( );
	drawItem( );
	drawAlter( );
	drawCasket( );
	Effect::getTask( )->drawEffect( );
	drawUI( );
	drawMovie( );
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

void RockViewer::drawBubble( ) const {
	RockFamilyPtr family( RockFamily::getTask( ) );
	RockClientInfoPtr info = RockClientInfo::getTask( );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		if ( !info->isActiveState( _status->getPlayer( i ).area ) ) {
			continue;
		}
		RockPlayerPtr player = family->getPlayer( i );
		if ( !player->isActive( ) ) {
			continue;
		}

		RockBubblePtr bubble = family->getBubble( i );
		if ( bubble->isActive( ) ) {
			ModelMV1Ptr model = bubble->getModel( );
			model->draw( );
		}
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
	std::list< ModelMDLPtr > shadows = shadow->getShadows( );
	std::list< ModelMDLPtr >::const_iterator ite = shadows.begin( );
	while ( ite != shadows.end( ) ) {
		ModelMDLPtr model = *ite;
		if ( !model ) {
			ite++;
			continue;
		}
		model->draw( );
		ite++;
	}
	shadow->clear( );
}

void RockViewer::drawUI( ) const {
	RockFamilyPtr family( RockFamily::getTask( ) );
	RockClientInfoPtr info = RockClientInfo::getTask( );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		if ( !info->isActiveState( _status->getPlayer( i ).area ) ||
			 _status->getPlayer( i ).area == STATE_RESULT ) {
			continue;
		}
		if ( family->getPlayer( i )->isBubble( ) &&
			 info->isActiveState( STATE_ENTRY ) ) {
			_breasts[ i ]->setRect( 0, 0, 320, 360 );
			_breasts[ i ]->setPos( i * ( SCREEN_WIDTH / 4 ), SCREEN_HEIGHT - 256, ( i + 1 ) * ( SCREEN_WIDTH / 4 ), SCREEN_HEIGHT );
			_breasts[ i ]->draw( );
			continue;
		}
		int player_status_pos = i * ( SCREEN_WIDTH / 4 );
		_image_frame->setPos( player_status_pos, DRAW_UI_Y );
		_image_frame->draw( );

		{//(POWER)
			int tw = HP_GRAPH_WIDTH * _status->getPlayer( i ).power;
			if ( tw != 0 ) {
				if( tw < 0 ) {
					tw = 0;
				}
				_status_ui->setRect( 0, 256, tw, HP_GRAPH_HEIGHT );
				int sx = player_status_pos + 160;
				int sy = DRAW_UI_Y + 50;
				_status_ui->setPos( sx, sy );
				_status_ui->draw( );
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
				_status_num->setRect( MONEY_GRAPH_WIDTH * num, 0, MONEY_GRAPH_WIDTH, MONEY_GRAPH_HEIGHT );
				_status_num->setPos( player_status_pos + -j * MONEY_GRAPH_WIDTH + 275, MONEY_Y );
				_status_num->draw( );
			}
		}

		{//(ITEM)
			unsigned int item = _status->getPlayer( i ).item;
			for ( int j = 0; j < MAX_ITEM_NUM; j++ ) {
				unsigned int check = 1 << j;
				if ( item & check ) {
					_status_ui->setRect( ITEM_GRAPH_SIZE * j, 320, ITEM_GRAPH_SIZE, ITEM_GRAPH_SIZE );
					int sx = player_status_pos + 135 + ITEM_DRAW_SIZE * j;
					int sy = ITEM_Y;
					_status_ui->setPos( sx, sy, sx + ITEM_DRAW_SIZE, sy + ITEM_DRAW_SIZE );
					_status_ui->draw( );
				}
			}
		}

		{// 徳表示
			int virtue = _status->getPlayer( i ).toku;
		
			int sx = player_status_pos + 290;
			int sy = ITEM_Y + ITEM_DRAW_SIZE;
			int digit = virtue == 0;
			while( virtue > 0 ) {
				digit++;
				virtue /= 10;
			}
			for ( int j = 0; j < digit; j++ ) {
				int num = _status->getPlayer( i ).toku % (int)pow( 10.0, (double)j + 1 );
				num /= (int)pow( 10.0, (double)j );
				_status_num->setRect( MONEY_GRAPH_WIDTH * num, 0, MONEY_GRAPH_WIDTH, MONEY_GRAPH_HEIGHT );
				_status_num->setPos( sx, sy );
				_status_num->draw( );
				sx -= MONEY_GRAPH_WIDTH;
			}
			sx -= ITEM_DRAW_SIZE;
			_status_ui->setRect( ITEM_GRAPH_SIZE * 7, 320, ITEM_GRAPH_SIZE, ITEM_GRAPH_SIZE );
			_status_ui->setPos( sx, sy,  sx + ITEM_DRAW_SIZE, sy + ITEM_DRAW_SIZE );
			_status_ui->draw( );
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
