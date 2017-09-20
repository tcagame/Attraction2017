#include "ViewerTitle.h"
#include "Drawer.h"
#include "Movie.h"

ViewerTitle::ViewerTitle( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_movie = MoviePtr( new Movie );
	_movie->load( "Resource/Ace/Event/title/ui_main_title.mp4" );
	_movie->play( true );
}

ViewerTitle::~ViewerTitle( ) {
}

void ViewerTitle::draw( ) {
	_movie->draw( );
}