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

	int n = 100;//data->getStatusProgress( );

	int sx = target * 320;
	int sy = 256 + 256;

	_image_frame->setPos( sx + 10, sy + 50 );
	_image_frame->draw( );
	_image_bar->setPos( sx + 10, sy + 50 );
	_image_bar->draw( );
}
