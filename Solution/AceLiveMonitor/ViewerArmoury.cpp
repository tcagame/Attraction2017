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
		int power = shot->getPower( ) - 1;
		int tx = 0 + power * 128 + 64 * ( shot->getCount( ) % 2 );
		int ty = 128;
		int sy1 = ( int )shot->getPos( ).y - NORMAL_CHAR_GRAPH_SIZE;
		int sx1 = ( int )( shot->getPos( ).x - camera_pos ) - ( NORMAL_CHAR_GRAPH_SIZE / 2 );
		int sx2 = sx1 + NORMAL_CHAR_GRAPH_SIZE;
		int dir = shot->getDir( );
		if ( dir == 1 ) {
			int tmp = sx1;
			sx1 = sx2;
			sx2 = tmp;
		}
		{
			_image->setRect( tx, ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
			_image->setPos( sx1, sy1, sx2, sy1 + NORMAL_CHAR_GRAPH_SIZE );
			_image->draw( );
		}
	}
}
