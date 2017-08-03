#include "ViewerArmoury.h"
#include "Drawer.h"
#include "Armoury.h"
#include "Family.h"
#include "Impact.h"
#include "Shot.h"

ViewerArmoury::ViewerArmoury( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_image_shot = drawer->createImage( "Effect/psychic.png" );
	_image_impact = drawer->createImage( "Effect/impact.png" );
}


ViewerArmoury::~ViewerArmoury( ) {
}

void ViewerArmoury::draw( ) const {
	drawShot( );
	drawImpact( );
}

void ViewerArmoury::drawShot( ) const {
	FamilyConstPtr family( Family::getTask( ) );
	int camera_pos = ( int )family->getCameraPos( );

	ArmouryPtr armoury( Armoury::getTask( ) );
	for ( int i = 0; i < armoury->getMaxShotNum( ); i++ ) {
		ShotConstPtr shot = armoury->getShot( i );
		if ( !shot ) {
			continue;
		}
		int add_sx = -camera_pos;
		int add_sy = VIEW_STREET_Y;
		if ( shot->getState( ) == Character::STATE_EVENT ) {
			add_sx = 0;
			add_sy = VIEW_EVENT_Y;
		}
		Chip chip = shot->getChip( );
		chip.sx1 += add_sx;
		chip.sx2 += add_sx;
		chip.sy1 += add_sy;
		chip.sy2 += add_sy;
		_image_shot->setRect( chip.tx, chip.ty, chip.size, chip.size );
		_image_shot->setPos( chip.sx1, chip.sy1, chip.sx2, chip.sy2 );
		_image_shot->draw( );
	}
}


void ViewerArmoury::drawImpact( ) const {
	FamilyConstPtr family( Family::getTask( ) );
	int camera_pos = ( int )family->getCameraPos( );
	std::list< ImpactPtr > impacts = Armoury::getTask( )->getImpactList( );
	std::list< ImpactPtr >::iterator ite = impacts.begin( );
	while ( ite != impacts.end( ) ) {
		ImpactPtr impact = (*ite);
		if ( !impact ) {
			ite++;
			continue;
		}
		int add_sx = -camera_pos;
		int add_sy = VIEW_STREET_Y;
		if ( impact->getState( ) == Character::STATE_EVENT ) {
			add_sx = 0;
			add_sy = VIEW_EVENT_Y;
		}
		Chip chip = impact->getChip( );
		chip.sx1 += add_sx;
		chip.sx2 += add_sx;
		chip.sy1 += add_sy;
		chip.sy2 += add_sy;
		_image_impact->setRect( chip.tx, chip.ty, chip.size, chip.size );
		_image_impact->setPos( chip.sx1, chip.sy1, chip.sx2, chip.sy2 );
		_image_impact->draw( );
		ite++;
	}
}
