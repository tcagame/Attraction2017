#include "ViewerProgress.h"
#include "SynchronousData.h"
#include "Drawer.h"
#include "Image.h"

ViewerProgress::ViewerProgress( ) {
	DrawerPtr drawer = Drawer::getTask( );
	_image_frame = drawer->createImage( "UI/ui_progress_frame.png" );
	_image_bar   = drawer->createImage( "UI/ui_progress_bar.png" );;
}

ViewerProgress::~ViewerProgress( ) {
}

void ViewerProgress::draw( PLAYER target ) {
	SynchronousDataPtr data( SynchronousData::getTask( ) );

	int sx = target * 320;
	int sy = 256 + 256;

	sx += 10;
	sy += 50;

	_image_frame->setPos( sx, sy );
	_image_frame->draw( );
	
	int n = data->getStatusProgress( target );
	if ( n > 0 ) {
		const int HEAD = 10;
		const int OX = 87;
		const int OY = 42;
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
