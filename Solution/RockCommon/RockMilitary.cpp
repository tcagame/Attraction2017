#include "RockMilitary.h"
#include "Application.h"
#include "Drawer.h"
#include "RockEnemy.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockImpact.h"
#include "RockPop.h"
#include "define.h"
#include "Effect.h"
#include "RockEnemyBoss.h"
#include "Sound.h"

RockMilitaryPtr RockMilitary::getTask( ) {
	return std::dynamic_pointer_cast< RockMilitary >( Application::getInstance( )->getTask( getTag( ) ) );
}


RockMilitary::RockMilitary( ) {
}


RockMilitary::~RockMilitary( ) {
}

void RockMilitary::initialize( ) {
}

std::list< RockEnemyPtr > RockMilitary::getEnemyList( ) const {
	return _enemies;
}

std::list< RockImpactPtr > RockMilitary::getImpactList( ) const {
	return _impacts;
}

void RockMilitary::update( ) {
	updateEnemies( );
	updateImpact( );
	updatePop( );
}

void RockMilitary::updateEnemies( ) {
	std::list< RockEnemyPtr >::iterator ite = _enemies.begin( );
	RockFamilyPtr family( RockFamily::getTask( ) );
	while ( ite != _enemies.end( ) ) {
		RockEnemyPtr enemy = (*ite);
		if ( !enemy ) {
			ite++;
			continue;
		}
		if ( enemy->isFinished( ) ) {
			add( RockImpactPtr( new RockImpact( enemy->getPos( ) + Vector( 0, 30, 0 ) ) ) );
			Sound::getTask( )->playSE( "yokai_se_26.wav" );
			enemy->dropItem( );
			enemy->reset( );
			if ( !std::dynamic_pointer_cast< RockEnemyBoss >( enemy ) ) {
				_pops.push_back( RockPopPtr( new RockPop( enemy ) ) );
			}
			ite = _enemies.erase( ite );
			continue;
		}

		enemy->update( );
		RockPlayerPtr overlapped_player = family->getOverLappedPlayer( enemy );
		if ( overlapped_player ) {
			enemy->adjustPosForOverLapped( overlapped_player );
		}
		RockEnemyPtr overlapped_enemy = getOverLappedEnemy( enemy );
		if ( overlapped_enemy ) {
			enemy->adjustPosForOverLapped( overlapped_enemy );
		}
		ite++;
	}
}

void RockMilitary::updateImpact( ) {
	std::list< RockImpactPtr >::iterator ite = _impacts.begin( );
	while ( ite != _impacts.end( ) ) {
		RockImpactPtr impact = *ite;
		if ( !impact ) {
			ite++;
			continue;
		}

		if ( impact->isFinished( ) ) {
			ite = _impacts.erase( ite );
			continue;
		}
		impact->update( );
		ite++;
	}
}

void RockMilitary::updatePop( ) {
	std::list< RockPopPtr >::iterator ite = _pops.begin( );
	while ( ite != _pops.end( ) ) {
		RockPopPtr pop = *ite;
		if ( !pop ) {
			ite++;
			continue;
		}
		pop->update( );
		if ( pop->isFinished( ) ) {
			ite = _pops.erase( ite );
			continue;
		}
		ite++;
	}
}

void RockMilitary::add( RockEnemyPtr enemy ) {
	_enemies.push_back( enemy );
}

void RockMilitary::add( RockImpactPtr impact ) {
	_impacts.push_back( impact );
}

void RockMilitary::clean( ) {
	_enemies = { };
	_impacts = { };
	_pops = { };
}


RockEnemyPtr RockMilitary::getOverLappedEnemy( RockCharacterPtr target ) const {
	RockEnemyPtr result = RockEnemyPtr( );
	std::list< RockEnemyPtr >::const_iterator ite = _enemies.begin( );
	while ( ite != _enemies.end( ) ) {
		RockEnemyPtr other = (*ite);
		if ( !other || other == target ) {
			ite++;
			continue;
		}
		if ( other->isOverLapped( target ) ) {
			result = other;
			break;
		}
		ite++;
	}
	return result;
}