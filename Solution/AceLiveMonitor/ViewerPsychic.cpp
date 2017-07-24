#include "ViewerPsychic.h"
#include "Drawer.h"


ViewerPsychic::ViewerPsychic( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_image = drawer->createImage( "Efect/psychic.png" );
}


ViewerPsychic::~ViewerPsychic( ) {
}

void ViewerPsychic::draw( ) const {
	for ( int i = 0; i < 0; i++ ) {
		int tx = 64;
		int ty = 128;
		int tx2 = 64;
		int ty2 = 64;
		int sy1 = NOMAL_CHAR_GRAPH_SIZE + NOMAL_CHAR_GRAPH_SIZE / 2;
		int sx1 = 0;
		int dir = 0;
		{
			_image->setRect( tx, ty, tx2, tx2 );
			_image->setPos( sx1, sy1, sx1 - NOMAL_CHAR_GRAPH_SIZE * dir, sy1 + NOMAL_CHAR_GRAPH_SIZE );
			_image->draw( );
		}
		{
			tx += 64;
			_image->setRect( tx, ty, tx2, tx2 );
			_image->setPos( sx1, sy1, sx1 - NOMAL_CHAR_GRAPH_SIZE * dir, sy1 + NOMAL_CHAR_GRAPH_SIZE );
			_image->draw( );
		}
	}
}
