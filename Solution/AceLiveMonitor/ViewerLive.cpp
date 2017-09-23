#include "ViewerLive.h"
#include "Application.h"
#include "Drawer.h"

#include "ViewerStreet.h"
#include "ViewerEvent.h"
#include "ViewerStatus.h"
#include "ViewerProgressBar.h"
#include "ViewerTitle.h"
#include "ViewerDebug.h"
#include "Debug.h"

#include "ViewerObject.h"
#include "SynchronousData.h"
#include "Family.h"
#include "Military.h"
#include "Storage.h"
#include "Magazine.h"
#include "Armoury.h"
#include "Office.h"

#include "World.h"
#include "Map.h"

const int EVENT_SX = 0;
const int EVENT_SY = 0;
const int MAIN_SX  = 0;
const int MAIN_SY  = 256;

ViewerLivePtr ViewerLive::getTask( ) {
	return std::dynamic_pointer_cast< ViewerLive >( Application::getInstance( )->getTask( getTag( ) ) );
}

ViewerLive::ViewerLive( ) {
}

ViewerLive::~ViewerLive( ) {
}

void ViewerLive::initialize( ) {
	_viewer_street   = ViewerStreetPtr     ( new ViewerStreet   );
	_viewer_event    = ViewerEventPtr	   ( new ViewerEvent    );
	_viewer_title    = ViewerTitlePtr      ( new ViewerTitle    );
	_viewer_status   = ViewerStatusPtr     ( new ViewerStatus   );
	_viewer_debug    = ViewerDebugPtr      ( new ViewerDebug    );
	_viewer_object   = ViewerObjectPtr     ( new ViewerObject   );
	
	DrawerPtr drawer = Drawer::getTask( );

	_image_bustup[ PLAYER_TAROSUKE ] = drawer->createImage( "UI/ui_bustup_tarosuke.png" );
	_image_bustup[ PLAYER_TAROJIRO ] = drawer->createImage( "UI/ui_bustup_tarojiro.png" );
	_image_bustup[ PLAYER_GARISUKE ] = drawer->createImage( "UI/ui_bustup_garisuke.png" );
	_image_bustup[ PLAYER_TAROMI   ] = drawer->createImage( "UI/ui_bustup_taromi.png"   );
	
	_image_message[ MESSAGE_GAMBLE0 ] = drawer->createImage( "UI/ui_dialogue_gamble.png" );
	_image_message[ MESSAGE_GAMBLE1 ] = drawer->createImage( "UI/ui_dialogue_gamble_han.png" );
	_image_message[ MESSAGE_GAMBLE2 ] = drawer->createImage( "UI/ui_dialogue_gamble_tyou.png" );
	_image_message[ MESSAGE_MIKO    ] = drawer->createImage( "UI/ui_dialogue_miko.png" );
	_image_message[ MESSAGE_RYUGU   ] = drawer->createImage( "UI/ui_dialogue_otohime.png" );
	_image_message[ MESSAGE_ENMA    ] = drawer->createImage( "UI/ui_dialogue1.png" );
	_image_message[ MESSAGE_BUDHA   ] = drawer->createImage( "UI/ui_dialogue2.png" );


	for ( int i = 0; i < MAX_MESSAGE; i++ ) {
		switch ( ( MESSAGE )i ) {
		case MESSAGE_GAMBLE0:
		case MESSAGE_GAMBLE1:
		case MESSAGE_GAMBLE2:
		case MESSAGE_RYUGU  :
			_image_message[ i ]->setRect( 0, 0, 320, 208 );
			_image_message[ i ]->setPos( 1280 - 320 - 7, 7 );
			break;
		case MESSAGE_MIKO   :
			_image_message[ i ]->setRect( 0, 0, 320, 208 );
			_image_message[ i ]->setPos( 400, 7 );
			break;
		case MESSAGE_ENMA   :
		case MESSAGE_BUDHA  :
			_image_message[ i ]->setRect( 0, 0, 320, 208 );
			_image_message[ i ]->setPos( 150, 10 );
			break;
		}
	}

	_image_frame = drawer->createImage( "UI/area_event_frame.png" );
	_image_frame->setRect( 0, 0, 1280, 256 );
	_image_frame->setPos( 0, 0 );
	
	_image_device = drawer->createImage( "UI/ui_device.png" );

	_image_fade = drawer->createImage( "UI/ui_fade.png" );
	_image_fade->setRect( 0, 0, 256, 256 );
	_image_fade->setPos( 0, 0, 1280, 256 );

	_image_redo = drawer->createImage( "UI/ui_continue_picture.png" );
	_image_entry = drawer->createImage( "UI/ui_entry1.png" );
	_image_continue = drawer->createImage( "UI/ui_continue1.png" );
}

void ViewerLive::update( ) {
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	
	// オブジェクトデータ同期
	data->resetObject( );
	Military::getTask( )->setSynchronousData( );
	Storage::getTask( )->setSynchronousData( );
	Office::getTask( )->setSynchronousData( );
	Family::getTask( )->setSynchronousData( );
	Magazine::getTask( )->setSynchronousData( );
	Armoury::getTask( )->setSynchronousData( );

	DrawerPtr drawer( Drawer::getTask( ) );
	drawer->waitForSync( );
	drawer->flip( );
	
	FamilyConstPtr family( Family::getTask( ) );
	int camera_pos = family->getCameraPosX( );

	// Main描画
	_viewer_street->draw( ViewerStreet::LAYER_BACK, MAIN_SX, MAIN_SY, camera_pos );
	_viewer_object->draw( AREA_STREET, MAIN_SX, MAIN_SY );
	
	if ( !Debug::getTask( )->isDebug( ) ) {
		_viewer_street->draw( ViewerStreet::LAYER_FRONT, MAIN_SX, MAIN_SY, camera_pos );
	}

	// イベント描画
	EVENT event = data->getEvent( );
	if ( event == EVENT_NONE ) {
		_viewer_title->draw( );
	} else {
		_viewer_event->draw( event, EVENT_SX, EVENT_SY );
	}

	// オブジェクト描画
	_viewer_object->draw( AREA_EVENT, EVENT_SX, EVENT_SY );
	
	// イベントフェード
	double ratio = data->getFade( ) / 100.0;
	_image_fade->setBlend( Image::BLEND_ALPHA, ratio );
	_image_fade->draw( );

	// イベント枠描画
	_image_frame->draw( );

	// ステータス描画
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		PLAYER target = ( PLAYER )i;
		_viewer_status->draw( target, i * VIEW_STATUS_WIDTH, VIEW_STATUS_Y );

		int count = data->getStatusProgressCount( target );

		switch ( data->getStatusState( target ) ) {
		case SynchronousData::STATE_ENTRY:
			{
				_image_entry->setPos( i * VIEW_STATUS_WIDTH, VIEW_STATUS_Y );
				_image_entry->draw( );
				int x = i * VIEW_STATUS_WIDTH + ( 320 - 122 ) / 2;
				int y = VIEW_STATUS_Y + 10;
				int height = 138 * count / 100;
				_image_bustup[ target ]->setRect( 0, 0, 122, 138 );
				_image_bustup[ target ]->setPos( x, y );
				_image_bustup[ target ]->setBlend( Image::BLEND_NONE, 0 );
				_image_bustup[ target ]->draw( );
				_image_bustup[ target ]->setRect( 0, 138 - height, 122, height);
				_image_bustup[ target ]->setPos( x, y + 138 - height );
				_image_bustup[ target ]->setBlend( Image::BLEND_ADD, 1.0 );
				_image_bustup[ target ]->draw( );
			}
			break;
		case SynchronousData::STATE_CONTINUE_FADE:
			{
				_image_continue->setPos( i * VIEW_STATUS_WIDTH, VIEW_STATUS_Y );
				_image_continue->draw( );
			}
			break;
		case SynchronousData::STATE_CONTINUE:
			{
				_image_continue->setPos( i * VIEW_STATUS_WIDTH, VIEW_STATUS_Y );
				_image_continue->draw( );
				int od = count * 50 / 100;
				int x = i * VIEW_STATUS_WIDTH + 160;
				int y = VIEW_STATUS_Y + 80;
				_image_redo->setRect( 0, 0, 32, 32 );
				_image_redo->setPos( x - od, y - od, x + od, y + od );
				_image_redo->draw( );
			}
			break;
		}

		if ( data->getStatusDevice( ( PLAYER )i ) < 0 ) {
			_image_device->setPos( i * 320 + 50, 600 );
			_image_device->draw( );
		}
	}

	//メッセージ
	drawMessage( );

	// デバッグ
	if ( Debug::getTask( )->isDebug( ) ) {
		_viewer_debug->draw( );
	}
}

void ViewerLive::drawMessage( ) {
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	switch ( data->getMessage( ) ) {
	case SynchronousData::MES_NONE:
		break;
	case SynchronousData::MES_GAMBLE0:
		_image_message[ MESSAGE_GAMBLE0 ]->draw( );
		break;
	case SynchronousData::MES_GAMBLE1:
		_image_message[ MESSAGE_GAMBLE1 ]->draw( );
		break;
	case SynchronousData::MES_GAMBLE2:
		_image_message[ MESSAGE_GAMBLE2 ]->draw( );
		break;
	case SynchronousData::MES_MIKO:
		_image_message[ MESSAGE_MIKO ]->draw( );
		break;
	case SynchronousData::MES_RYUGU:
		_image_message[ MESSAGE_RYUGU ]->draw( );
		break;
	case SynchronousData::MES_ENMA:
		_image_message[ MESSAGE_ENMA ]->draw( );
		break;
	case SynchronousData::MES_BUDHA:
		_image_message[ MESSAGE_BUDHA ]->draw( );
		break;
	}
}