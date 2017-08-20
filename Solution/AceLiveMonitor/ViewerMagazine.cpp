#include "ViewerMagazine.h"
#include "Family.h"
#include "Magazine.h"
#include "Impact.h"
#include "Drawer.h"

ViewerMagazine::ViewerMagazine( ) {
	_impact = Drawer::getTask( )->createImage( "Effect/impact.png" );
}


ViewerMagazine::~ViewerMagazine( ) {
}

void ViewerMagazine::draw( ) const {

	FamilyConstPtr family( Family::getTask( ) );
	int camera_pos = ( int )family->getCameraPos( );
	std::list< ImpactPtr > impacts = Magazine::getTask( )->getImpactList( );
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
		_impact->setRect( chip.tx, chip.ty, chip.size, chip.size );
		_impact->setPos( chip.sx1, chip.sy1, chip.sx2, chip.sy2 );
		_impact->draw( );
		ite++;
	}
}