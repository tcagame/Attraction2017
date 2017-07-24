#include "Viewer.h"
#include "Family.h"
#include "Player.h"
#include "Psychic.h"
#include "PsychicManager.h"
#include <string>

#include "Drawer.h"
#include "ViewerFamily.h"
#include "ViewerStreet.h"
#include "ViewerPsychic.h"


Viewer::Viewer( ) {
}


Viewer::~Viewer( ) {
}

void Viewer::update( ) {
	Drawer::getTask( )->flip( );
//	_viewer_family->draw( );
//	_viewer_street->draw( );
//	_viewer_psychic->draw( );
}

