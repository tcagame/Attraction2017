#include "ViewerConsole.h"
#include "Application.h"
#include "Drawer.h"
#include "ViewerObject.h"
#include "SynchronousData.h"
#include "Client.h"

const int EVENT_SX = -256;
const int EVENT_SY = 0;
const int MAIN_SX  = -256;
const int MAIN_SY  = 480 - 256;

ViewerConsolePtr ViewerConsole::getTask( ) {
	return std::dynamic_pointer_cast< ViewerConsole >( Application::getInstance( )->getTask( getTag( ) ) );
}

ViewerConsole::ViewerConsole( ) {
}

ViewerConsole::~ViewerConsole( ) {
}

void ViewerConsole::initialize( ) {
	DrawerPtr drawer( Drawer::getTask( ) );

	_viewer_object = ViewerObjectPtr  ( new ViewerObject );

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
	// Main描画
	//_viewer_street->draw( ViewerStreet::LAYER_BACK );
	_viewer_object->draw( AREA_MAIN, MAIN_SX, MAIN_SY );
	//_viewer_street->draw( ViewerStreet::LAYER_FRONT );

	// イベント描画
	//_viewer_event->draw( );
	_viewer_object->draw( AREA_EVENT, EVENT_SX, EVENT_SY );
}

void ViewerConsole::drawUI( ) {
	_image_bar_upper->draw( );
	_image_bar_lower->draw( );
	_image_status->draw( );
	_image_minimap->draw( );

}
