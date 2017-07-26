#include "ViewerFamily.h"
#include "Family.h"
#include "Player.h"
#include "Drawer.h"


ViewerFamily::ViewerFamily( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_image[ 0 ] = drawer->createImage( "Family/tarosuke.png" );
	_image[ 1 ] = drawer->createImage( "Family/tarojiro.png" );
	_image[ 2 ] = drawer->createImage( "Family/garisuke.png" );
	_image[ 3 ] = drawer->createImage( "Family/taromi.png" );
}


ViewerFamily::~ViewerFamily( ) {

}

void ViewerFamily::draw( ) const {
	FamilyPtr family( Family::getTask( ) );
	for ( int i = 0; i < ACE_PLAYER_NUM; i++ ) {
		PlayerConstPtr player = family->getPlayer( i );
		Vector pos = player->getPos( );
		Chip chip = player->getChip( );
		chip.sx1 -= ( int )family->getCameraPos( );
		chip.sx2 -= ( int )family->getCameraPos( );
		_image[ i ]->setRect( chip.tx, chip.ty, chip.size, chip.size );
		_image[ i ]->setPos( chip.sx1, chip.sy1, chip.sx2, chip.sy2 );
		_image[ i ]->draw( );
	}
}
