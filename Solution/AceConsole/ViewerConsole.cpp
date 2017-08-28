#include "ViewerConsole.h"
#include "Application.h"
#include "Drawer.h"
#include "ViewerObject.h"
#include "ViewerStreet.h"
#include "ViewerEvent.h"
#include "SynchronousData.h"
#include "Client.h"
#include "MapStreet.h"

const int AREA_SX  = 0;
const int AREA_SY  = 480 - 256;

ViewerConsolePtr ViewerConsole::getTask( ) {
	return std::dynamic_pointer_cast< ViewerConsole >( Application::getInstance( )->getTask( getTag( ) ) );
}

ViewerConsole::ViewerConsole( PLAYER player ) :
_player( player ){
}

ViewerConsole::~ViewerConsole( ) {
}

void ViewerConsole::initialize( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	MapStreetPtr map( new MapStreet );

	_viewer_object = ViewerObjectPtr( new ViewerObject );
	_viewer_street = ViewerStreetPtr( new ViewerStreet( map->getPageNum( ) ) );
	_viewer_event  = ViewerEventPtr	( new ViewerEvent );

	_image_bar_upper = drawer->createImage( "UI/ui_bar.png" );
	_image_bar_upper->setRect( 0, 0, 640, 8 );
	_image_bar_upper->setPos( 0, 0 );

	_image_bar_lower = drawer->createImage( "UI/ui_bar.png" );
	_image_bar_lower->setRect( 0, 0, 640, 8 );
	_image_bar_lower->setPos( 0, 208 + 8 );

	_image_status = drawer->createImage( "UI/status_plate.png" );
	_image_status->setRect( 0, 0, 320, 208 );
	_image_status->setPos( 0, 8 );

	_image_minimap = drawer->createImage( "UI/ui_minimap.png" );
	_image_minimap->setRect( 0, 0, 320, 208 );
	_image_minimap->setPos( 320, 8 );
}

void ViewerConsole::update( ) {
	ClientPtr client( Client::getTask( ) );
	if ( !client->isRecievingUDP( ) ) {
		return;
	}
	DrawerPtr drawer( Drawer::getTask( ) );
	drawer->flip( );

	drawArea( );
	drawUI( );

	// ステータス描画
	//_viewer_status->draw( );
	if ( Client::getTask( )->getPhase( ) == "PHASE_CONNECTING" ) {
		Drawer::getTask( )->drawString( 0, 0, "CONNECTING" );
	} else {
		Drawer::getTask( )->drawString( 0, 0, "NOT_CONNECTING" );
	}
}

void ViewerConsole::drawArea( ) {
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	unsigned char state = data->getStatusState( _player );

	switch ( state ) {
	case SynchronousData::STATE_PLAY_STREET:
		drawAreaStreet( );
		break;
	case SynchronousData::STATE_PLAY_EVENT:
		drawAreaEvent( );
		break;
	}
}

void ViewerConsole::drawAreaStreet( ) {
	SynchronousDataPtr data( SynchronousData::getTask( ) );

	int camera_pos = data->getStatusX( _player ) - 320;
	int offset_x = data->getStatusX( _player ) - data->getCameraX( ) - 320;
	// Main描画
	_viewer_street->draw( ViewerStreet::LAYER_BACK, AREA_SX, AREA_SY, camera_pos );
	_viewer_object->draw( AREA_STREET, AREA_SX - offset_x, AREA_SY );
	_viewer_street->draw( ViewerStreet::LAYER_FRONT, AREA_SX, AREA_SY, camera_pos );
}

void ViewerConsole::drawAreaEvent( ) {
	SynchronousDataPtr data( SynchronousData::getTask( ) );

	int camera_pos = data->getStatusX( _player ) - 320;
	if ( camera_pos < 0 ) {
		camera_pos = 0;
	}
	if ( camera_pos > 1280 - 640 - 1 ) {
		camera_pos = 1280 - 640 - 1;
	}

	// イベント描画
	EVENT event = data->getEvent( );
	if ( event == EVENT_NONE ) {
		return;
	}
	_viewer_event->draw( event, AREA_SX - camera_pos, AREA_SY );
	_viewer_object->draw( AREA_EVENT, AREA_SX - camera_pos, AREA_SY );
}

void ViewerConsole::drawUI( ) {
	_image_bar_upper->draw( );
	_image_bar_lower->draw( );
	_image_status->draw( );
	_image_minimap->draw( );

}
