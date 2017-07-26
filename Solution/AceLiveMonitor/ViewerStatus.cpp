#include "ViewerStatus.h"
#include "Drawer.h"
#include "ace_define.h"


ViewerStatus::ViewerStatus( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_status_flame = drawer->createImage( "UI/status_plate.png" );
}

ViewerStatus::~ViewerStatus( ) {
}

void ViewerStatus::draw( ) const {
	for ( int i = 0; i < ACE_PLAYER_NUM; i++ ) {
		int sx = i * 320;
		_status_flame->setPos( sx, VIEW_STATUS_Y );
		_status_flame->draw( );
	}
}