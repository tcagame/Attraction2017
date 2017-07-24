#include "ViewerShot.h"
#include "Drawer.h"
#include "Armoury.h"

ViewerShot::ViewerShot( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_image = drawer->createImage( "Effect/psychic.png" );
}


ViewerShot::~ViewerShot( ) {
}

void ViewerShot::draw( ) const {
	ArmouryPtr armoury( Armoury::getTask( ) );
	std::vector< ShotPtr > shot_list = armoury->getShotList( );
	if ( shot_list.empty( ) ) {
		return;
	}

	std::vector< ShotPtr >::iterator ite = shot_list.begin( );
	while ( ite != shot_list.end( ) ) {
		ShotPtr shot = ( *ite );
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
		ite++;
	}
}
