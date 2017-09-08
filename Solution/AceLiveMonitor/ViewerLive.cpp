#include "ViewerLive.h"
#include "Application.h"
#include "Drawer.h"

#include "ViewerStreet.h"
#include "ViewerEvent.h"
#include "ViewerStatus.h"
#include "ViewerProgress.h"
#include "ViewerTitle.h"
#include "ViewerDebug.h"
#include "Debug.h"

#include "ViewerObject.h"
#include "SynchronousData.h"
#include "Family.h"

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
	_viewer_street   = ViewerStreetPtr  ( new ViewerStreet   );
	_viewer_event    = ViewerEventPtr	( new ViewerEvent    );
	_viewer_title    = ViewerTitlePtr   ( new ViewerTitle    );
	_viewer_status   = ViewerStatusPtr  ( new ViewerStatus   );
	_viewer_progress = ViewerProgressPtr( new ViewerProgress );
	_viewer_debug    = ViewerDebugPtr   ( new ViewerDebug    );
	_viewer_object   = ViewerObjectPtr  ( new ViewerObject   );

	DrawerPtr drawer = Drawer::getTask( );
	
	_image_frame = drawer->createImage( "UI/area_event_frame.png" );
	_image_frame->setRect( 0, 0, 1280, 256 );
	_image_frame->setPos( 0, 0 );
	
	_image_cover_entry    = drawer->createImage( "UI/ui_cover_entry.png" );
	_image_cover_continue = drawer->createImage( "UI/ui_cover_continue.png" );

	_image_device = drawer->createImage( "UI/ui_device.png" );
}

void ViewerLive::update( ) {
	SynchronousDataPtr data( SynchronousData::getTask( ) );

	DrawerPtr drawer( Drawer::getTask( ) );
	drawer->waitForSync( );
	drawer->flip( );
	
	FamilyConstPtr family( Family::getTask( ) );
	int camera_pos = family->getCameraPosX( );

	// Main描画
	_viewer_street->draw( ViewerStreet::LAYER_BACK, MAIN_SX, MAIN_SY, camera_pos );
	_viewer_object->draw( AREA_STREET, MAIN_SX, MAIN_SY );
	_viewer_street->draw( ViewerStreet::LAYER_FRONT, MAIN_SX, MAIN_SY, camera_pos );

	// イベント描画
	EVENT event = data->getEvent( );
	if ( event == EVENT_NONE ) {
		_viewer_title->draw( );
	} else {
		_viewer_event->draw( event, EVENT_SX, EVENT_SY );
	}

	// イベント枠描画
	_image_frame->draw( );

	// オブジェクト描画
	_viewer_object->draw( AREA_EVENT, EVENT_SX, EVENT_SY );
	
	// ステータス描画
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		PLAYER target = ( PLAYER )i;
		_viewer_status->draw( target, i * VIEW_STATUS_WIDTH, VIEW_STATUS_Y );

		switch ( data->getStatusState( target ) ) {
		case SynchronousData::STATE_ENTRY:
			_image_cover_entry->setPos( i * VIEW_STATUS_WIDTH, VIEW_STATUS_Y );
			_image_cover_entry->draw( );
			_viewer_progress->draw( target );
			break;
		case SynchronousData::STATE_CONTINUE:
			_image_cover_continue->setPos( i * VIEW_STATUS_WIDTH, VIEW_STATUS_Y );
			_image_cover_continue->draw( );
			_viewer_progress->draw( target );
			break;
		}

		if ( data->getStatusDevice( ( PLAYER )i ) < 0 ) {
			_image_device->setPos( i * 320 + 50, 600 );
			_image_device->draw( );
		}
	}

	// デバッグ
	if ( Debug::getTask( )->isDebug( ) ) {
		_viewer_debug->draw( );
	}

	// 同期データ初期化
	data->resetObject( );
}
