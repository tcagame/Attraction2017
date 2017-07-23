#include "Viewer.h"
#include "Family.h"
#include "Player.h"
#include "Drawer.h"

const int PLAYER_CHIP_SIZE = 64;
const int PLAYER_FOOT = 7;

Viewer::Viewer( FamilyConstPtr family ) :
_family( family ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_image_family[ 0 ] = drawer->createImage( "Family/tarosuke.png" );
	_image_family[ 1 ] = drawer->createImage( "Family/tarojiro.png" );
	_image_family[ 2 ] = drawer->createImage( "Family/garisuke.png" );
	_image_family[ 3 ] = drawer->createImage( "Family/taromi.png" );
}


Viewer::~Viewer( ) {
}

void Viewer::update( ) {
	Drawer::getTask( )->flip( );
	drawFamily( );
}

void Viewer::drawFamily( ) const {
	for ( int i = 0; i < ACE_PLAYER_NUM; i++ ) {
		Vector pos = _family->getPlayer( i )->getPos( );
		_image_family[ i ]->setRect( 0, 0, PLAYER_CHIP_SIZE, PLAYER_CHIP_SIZE );
		_image_family[ i ]->setPos( (int)pos.x - PLAYER_CHIP_SIZE / 2, (int)pos.y - PLAYER_CHIP_SIZE + PLAYER_FOOT );
		_image_family[ i ]->draw( );
	}
}