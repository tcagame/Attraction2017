#include "ViewerConsole.h"
#include "Application.h"
#include "Drawer.h"
#include "ViewerObject.h"
#include "SynchronousData.h"
#include "Client.h"

const int EVENT_SX = 0;
const int EVENT_SY = 0;
const int MAIN_SX  = 0;
const int MAIN_SY  = 256;

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
}

void ViewerConsole::update( ) {

	DrawerPtr drawer( Drawer::getTask( ) );
	drawer->flip( );

	// Main描画
	//_viewer_street->draw( ViewerStreet::LAYER_BACK );
	_viewer_object->draw( AREA_MAIN, MAIN_SX, MAIN_SY );
	//_viewer_street->draw( ViewerStreet::LAYER_FRONT );

	// イベント描画
	//_viewer_event->draw( );
	//_viewer_object->draw( AREA_EVENT, EVENT_SX, EVENT_SY );
	
	// ステータス描画
	//_viewer_status->draw( );
	if ( Client::getTask( )->getPhase( ) == "PHASE_CONNECTING" ) {
		Drawer::getTask( )->drawString( 0, 0, "CONNECTING" );
	} else {
		Drawer::getTask( )->drawString( 0, 0, "NOT_CONNECTING" );
	}
}
