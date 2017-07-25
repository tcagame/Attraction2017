#include "Viewer.h"
#include "Application.h"
#include "Drawer.h"

#include "ViewerFamily.h"
#include "ViewerStreet.h"
#include "ViewerArmoury.h"

ViewerPtr Viewer::getTask( ) {
	return std::dynamic_pointer_cast< Viewer >( Application::getInstance( )->getTask( getTag( ) ) );
}

Viewer::Viewer( ) {
}

Viewer::~Viewer( ) {
}

void Viewer::initialize( ) {
	_viewer_family  = ViewerFamilyPtr ( new ViewerFamily ); 
	_viewer_street  = ViewerStreetPtr ( new ViewerStreet );
	_viewer_armoury = ViewerArmouryPtr( new ViewerArmoury );
}

void Viewer::update( ) {
	Drawer::getTask( )->flip( );
	_viewer_street->draw( );
	_viewer_family->draw( );
	_viewer_armoury->draw( );
}
