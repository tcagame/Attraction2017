#include "ViewerMilitary.h"
#include "Military.h"
#include "Enemy.h"
#include "ace_define.h"
#include "Drawer.h"
#include "Family.h"
#include "Impact.h"

ViewerMilitary::ViewerMilitary( ImagePtr impact ) :
_impact( impact ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_enemy_small = drawer->createImage( "Enemy/enemy_small.png" );
	_enemy_midium = drawer->createImage( "Enemy/enemy_medium.png" );
	_enemy_wide = drawer->createImage( "Enemy/enemy_big.png" );
	_enemy_boss = drawer->createImage( "Enemy/enemy_boss.png" );
}


ViewerMilitary::~ViewerMilitary( ) {
}

void ViewerMilitary::draw( ) const {
	drawEnemyies( );
	drawImpacts( );
}

void ViewerMilitary::drawEnemyies( ) const {
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
			if ( chip.size == SMALL_CHAR_GRAPH_SIZE ) {
				_enemy_small->setRect( chip.tx, chip.ty, chip.size, chip.size );
				_enemy_small->setPos( chip.sx1, chip.sy1, chip.sx2, chip.sy2 );
				_enemy_small->draw( );
			}
			if ( chip.size == NORMAL_CHAR_GRAPH_SIZE ) {
				_enemy_midium->setRect( chip.tx, chip.ty, chip.size, chip.size );
				_enemy_midium->setPos( chip.sx1, chip.sy1, chip.sx2, chip.sy2 );
				_enemy_midium->draw( );
			}
			if ( chip.size == BIG_CHAR_GRAPH_SIZE ) {
				_enemy_wide->setRect( chip.tx, chip.ty, chip.size, chip.size );
				_enemy_wide->setPos( chip.sx1, chip.sy1, chip.sx2, chip.sy2 );
				_enemy_wide->draw( );
			}
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
			_enemy_boss->setRect( chip.tx, chip.ty, chip.size, chip.size );
			_enemy_boss->setPos( chip.sx1, chip.sy1, chip.sx2, chip.sy2 );
			_enemy_boss->draw( );
		}
		{
			Chip chip = boss->getChip2( );
			chip.sy1 += VIEW_EVENT_Y;
			chip.sy2 += VIEW_EVENT_Y;
			_enemy_boss->setRect( chip.tx, chip.ty, chip.size, chip.size );
			_enemy_boss->setPos( chip.sx1, chip.sy1, chip.sx2, chip.sy2 );
			_enemy_boss->draw( );
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
			_enemy_boss->setRect( chip.tx, chip.ty, chip.size, chip.size );
			_enemy_boss->setPos( chip.sx1, chip.sy1, chip.sx2, chip.sy2 );
			_enemy_boss->draw( );
			ite++;
		}
	}
}

void ViewerMilitary::drawImpacts( ) const {
	FamilyConstPtr family( Family::getTask( ) );
	int camera_pos = ( int )family->getCameraPos( );
	std::list< ImpactPtr > impacts = Military::getTask( )->getImpactList( );
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