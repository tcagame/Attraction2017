#include "ViewerFamily.h"
#include "Family.h"
#include "Player.h"
#include "Drawer.h"

const int PLAYER_FOOT = 7;

ViewerFamily::ViewerFamily( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_image_family[ 0 ] = drawer->createImage( "Family/tarosuke.png" );
	_image_family[ 1 ] = drawer->createImage( "Family/tarojiro.png" );
	_image_family[ 2 ] = drawer->createImage( "Family/garisuke.png" );
	_image_family[ 3 ] = drawer->createImage( "Family/taromi.png" );
}


ViewerFamily::~ViewerFamily( ) {

}

void ViewerFamily::draw( ) const {
	FamilyPtr family( Family::getTask( ) );
	for ( int i = 0; i < ACE_PLAYER_NUM; i++ ) {
		PlayerConstPtr player = family->getPlayer( i );
		Vector pos = player->getPos( );
		Player::ACTION action = player->getAction( );
		int cx = 0;
		int cy = 0;
		player->getChipIndex( cx, cy );
		int tx = cx * NOMAL_CHAR_GRAPH_SIZE;
		int ty = cy * NOMAL_CHAR_GRAPH_SIZE;
		_image_family[ i ]->setRect( tx, ty, NOMAL_CHAR_GRAPH_SIZE, NOMAL_CHAR_GRAPH_SIZE );
		if ( player->getDir( ) == Player::DIR_LEFT ) {
			int sx = (int)pos.x - NOMAL_CHAR_GRAPH_SIZE / 2;
			int sy = (int)pos.y - NOMAL_CHAR_GRAPH_SIZE + PLAYER_FOOT;
			_image_family[ i ]->setPos( sx, sy );
		} else {
			int sx = (int)pos.x - NOMAL_CHAR_GRAPH_SIZE / 2 + NOMAL_CHAR_GRAPH_SIZE;
			int sy = (int)pos.y - NOMAL_CHAR_GRAPH_SIZE + PLAYER_FOOT;
			_image_family[ i ]->setPos( sx, sy, sx - NOMAL_CHAR_GRAPH_SIZE, sy + NOMAL_CHAR_GRAPH_SIZE );
		}
		_image_family[ i ]->draw( );
	}
}