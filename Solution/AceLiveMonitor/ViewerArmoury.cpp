#include "ViewerArmoury.h"
#include "Drawer.h"
#include "Armoury.h"

ViewerArmoury::ViewerArmoury( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_image = drawer->createImage( "Effect/psychic.png" );
}


ViewerArmoury::~ViewerArmoury( ) {
}

void ViewerArmoury::draw( ) const {
	ArmouryPtr armoury( Armoury::getTask( ) );
	for ( int i = 0; i < Armoury::MAX_SHOT_NUM; i++ ) {
		ShotConstPtr shot = armoury->getShot( i );
		if ( !shot ) {
			continue;
		}

		int tx = 64;
		int ty = 128;
		int tx2 = 64;
		int ty2 = 64;
		int sy1 = (int)shot->getPos( ).y - NOMAL_CHAR_GRAPH_SIZE;
		int sx1 = (int)shot->getPos( ).x + NOMAL_CHAR_GRAPH_SIZE / 2;
		int dir = shot->getDir( );
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
