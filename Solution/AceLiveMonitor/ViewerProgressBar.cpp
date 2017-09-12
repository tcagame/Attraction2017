#include "ViewerProgressBar.h"
#include "SynchronousData.h"
#include "Drawer.h"
#include "Image.h"

ViewerProgressBar::ViewerProgressBar( ) {
	DrawerPtr drawer = Drawer::getTask( );
	_image_bar   = drawer->createImage( "UI/ui_progress_bar.png" );;
}

ViewerProgressBar::~ViewerProgressBar( ) {
}

void ViewerProgressBar::draw( PLAYER target ) {
	SynchronousDataPtr data( SynchronousData::getTask( ) );

	int sx = target * 320;
	int sy = 256 + 256;

	int n = data->getStatusProgressCount( target );
	if ( n > 0 ) {
		const int HEAD = 10;
		const int OX = 87;
		const int OY = 134;
		_image_bar->setRect( 0, 0, HEAD, 20 );
		_image_bar->setPos( sx + OX, sy + OY );
		_image_bar->draw( );

		int width = ( 144 - HEAD * 2 ) * n / 100;
		_image_bar->setRect( HEAD, 0, width, 20 );
		_image_bar->setPos( sx + OX + HEAD, sy + OY );
		_image_bar->draw( );

		_image_bar->setRect( HEAD + ( 144 - HEAD * 2 ), 0, HEAD, 20 );
		_image_bar->setPos( sx + OX + HEAD + width, sy + OY );
		_image_bar->draw( );
	}
}
