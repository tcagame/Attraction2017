#include "Viewer.h"
#include "Application.h"
#include "Drawer.h"
#include "Keyboard.h"

#include "ViewerFamily.h"
#include "ViewerStreet.h"
#include "ViewerArmoury.h"
#include "ViewerMilitary.h"
#include "ViewerEvent.h"
#include "ViewerStatus.h"

#include "ViewerDebug.h"

ViewerPtr Viewer::getTask( ) {
	return std::dynamic_pointer_cast< Viewer >( Application::getInstance( )->getTask( getTag( ) ) );
}

Viewer::Viewer( ) :
_debug( false ) {
}

Viewer::~Viewer( ) {
}

void Viewer::initialize( ) {
	_viewer_family  = ViewerFamilyPtr ( new ViewerFamily ); 
	_viewer_street  = ViewerStreetPtr ( new ViewerStreet );
	_viewer_armoury = ViewerArmouryPtr( new ViewerArmoury );
	_viewer_military = ViewerMilitaryPtr( new ViewerMilitary );
	_viewer_event   = ViewerEventPtr  ( new ViewerEvent );
	_viewer_status  = ViewerStatusPtr ( new ViewerStatus );

	_viewer_debug = ViewerDebugPtr( new ViewerDebug );
}

void Viewer::update( ) {
	if ( Keyboard::getTask( )->isPushKey( "SPACE" ) ) {
		_debug = !_debug;
	}

	Drawer::getTask( )->flip( );
	_viewer_event->draw( );
	_viewer_status->draw( );
	_viewer_street->draw( ViewerStreet::LAYER_BACK );
	_viewer_military->draw( );
	_viewer_family->draw( );
	_viewer_armoury->draw( );
	//_viewer_street->draw( ViewerStreet::LAYER_FRONT );
	if ( _debug ) {
		_viewer_debug->draw( );
	}
}
