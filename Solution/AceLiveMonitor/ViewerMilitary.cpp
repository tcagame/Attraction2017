#include "ViewerMilitary.h"
#include "Military.h"
#include "Enemy.h"
#include "ace_define.h"
#include "Drawer.h"
#include "Family.h"

ViewerMilitary::ViewerMilitary( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_image = drawer->createImage( "Enemy/enemy_medium.png" );
}


ViewerMilitary::~ViewerMilitary( ) {
}

void ViewerMilitary::draw( ) const {
	FamilyConstPtr family( Family::getTask( ) );
	int camera_pos = ( int )family->getCameraPos( );
	MilitaryConstPtr military( Military::getTask( ) );
	std::list< EnemyPtr > enemies = military->getList( );
	std::list< EnemyPtr >::const_iterator ite = enemies.begin( );
	while ( ite != enemies.end( ) ) {
		EnemyPtr enemy = (*ite);
		if ( !enemy ) {
			ite++;
			continue;
		}
		Chip chip = enemy->getChip( );
		chip.sx1 -= camera_pos;
		chip.sx2 -= camera_pos;
		_image->setRect( chip.tx, chip.ty, chip.size, chip.size );
		_image->setPos( chip.sx1, chip.sy1, chip.sx2, chip.sy2 );
		_image->draw( );
		ite++;
	}
}
