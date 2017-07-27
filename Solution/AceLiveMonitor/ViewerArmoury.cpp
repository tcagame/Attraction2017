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
	int camera_pos = ( int )family->getCameraPos( );

	ArmouryPtr armoury( Armoury::getTask( ) );
	for ( int i = 0; i < armoury->getMaxShotNum( ); i++ ) {
		ShotConstPtr shot = armoury->getShot( i );
		if ( !shot ) {
			continue;
		}		
		Chip chip = shot->getChip( );
		chip.sx1 -= camera_pos;
		chip.sx2 -= camera_pos;
		{
			_image->setRect( chip.tx, chip.ty, chip.size, chip.size );
			_image->setPos( chip.sx1, chip.sy1, chip.sx2, chip.sy2 );
		}
		{
			chip.tx += 64;
			_image->setRect( chip.tx, chip.ty, chip.size, chip.size );
			_image->setPos( chip.sx1, chip.sy1, chip.sx2, chip.sy2 );
		}
		_image->draw( );
	}
}
