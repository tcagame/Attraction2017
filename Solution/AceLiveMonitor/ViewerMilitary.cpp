#include "ViewerMilitary.h"
#include "Military.h"
#include "Enemy.h"
#include "ace_define.h"
#include "Drawer.h"
#include "Family.h"

ViewerMilitary::ViewerMilitary( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_image_enemy = drawer->createImage( "Enemy/enemy_medium.png" );
	_image_boss = drawer->createImage( "Enemy/enemy_boss.png" );
}


ViewerMilitary::~ViewerMilitary( ) {
}

void ViewerMilitary::draw( ) const {
	FamilyConstPtr family( Family::getTask( ) );
	int camera_pos = ( int )family->getCameraPos( );
	MilitaryConstPtr military( Military::getTask( ) );

	{//enemy_list
		std::list< EnemyPtr > enemies = military->getEnemyList( );
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
			chip.sy1 += VIEW_STREET_Y;
			chip.sy2 += VIEW_STREET_Y;
			_image_enemy->setRect( chip.tx, chip.ty, chip.size, chip.size );
			_image_enemy->setPos( chip.sx1, chip.sy1, chip.sx2, chip.sy2 );
			_image_enemy->draw( );
			ite++;
		}
	}

	//enemy_boss
	EnemyPtr boss = military->getBoss( );
	if ( boss ) {
		{
			Chip chip = boss->getChip( );
			chip.sy1 += VIEW_EVENT_Y;
			chip.sy2 += VIEW_EVENT_Y;
			_image_boss->setRect( chip.tx, chip.ty, chip.size, chip.size );
			_image_boss->setPos( chip.sx1, chip.sy1, chip.sx2, chip.sy2 );
			_image_boss->draw( );
		}
		{
			Chip chip = boss->getChip2( );
			chip.sy1 += VIEW_EVENT_Y;
			chip.sy2 += VIEW_EVENT_Y;
			_image_boss->setRect( chip.tx, chip.ty, chip.size, chip.size );
			_image_boss->setPos( chip.sx1, chip.sy1, chip.sx2, chip.sy2 );
			_image_boss->draw( );
		}
	}
	{//event_enemy
		std::list< EnemyPtr > enemies = military->getEventEnemyList( );
		std::list< EnemyPtr >::const_iterator ite = enemies.begin( );
		while ( ite != enemies.end( ) ) {
			EnemyPtr enemy = (*ite);
			if ( !enemy ) {
				ite++;
				continue;
			}
			Chip chip = enemy->getChip( );
			chip.sy1 += VIEW_EVENT_Y;
			chip.sy2 += VIEW_EVENT_Y;
			_image_boss->setRect( chip.tx, chip.ty, chip.size, chip.size );
			_image_boss->setPos( chip.sx1, chip.sy1, chip.sx2, chip.sy2 );
			_image_boss->draw( );
			ite++;
		}
	}
}
