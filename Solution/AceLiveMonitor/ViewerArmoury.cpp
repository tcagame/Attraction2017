#include "ViewerArmoury.h"
#include "Drawer.h"
#include "Armoury.h"
#include "Family.h"

ViewerArmoury::ViewerArmoury( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_image = drawer->createImage( "Effect/psychic.png" );
}


ViewerArmoury::~ViewerArmoury( ) {
}

void ViewerArmoury::draw( ) const {
	FamilyConstPtr family( Family::getTask( ) );
	double camera_pos = family->getCameraPos( );

	ArmouryPtr armoury( Armoury::getTask( ) );
	for ( int i = 0; i < armoury->getMaxShotNum( ); i++ ) {
		ShotConstPtr shot = armoury->getShot( i );
		if ( !shot ) {
			continue;
		}

		int tx = 64;
		int ty = 128;
		int tx2 = 64;
		int ty2 = 64;
		int sy1 = ( int )shot->getPos( ).y - NORMAL_CHAR_GRAPH_SIZE;
		int sx1 = ( int )( shot->getPos( ).x - camera_pos ) - ( NORMAL_CHAR_GRAPH_SIZE / 2 ) + ( SCREEN_WIDTH / 2 );
		int sx2 = sx1 + NORMAL_CHAR_GRAPH_SIZE;
		int dir = shot->getDir( );
		if ( dir == 1 ) {
			int tmp = sx1;
			sx1 = sx2;
			sx2 = tmp;
		}
		{
			_image->setRect( tx, ty, tx2, tx2 );
			_image->setPos( sx1, sy1, sx2, sy1 + NORMAL_CHAR_GRAPH_SIZE );
			_image->draw( );
		}
		{
			tx += 64;
			_image->setRect( tx, ty, tx2, tx2 );
			_image->setPos( sx1, sy1, sx2, sy1 + NORMAL_CHAR_GRAPH_SIZE );
			_image->draw( );
		}
	}
}
