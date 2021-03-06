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
#include "RockEnemyAttack.h"
#include "Sound.h"

PTR( RockEnemyBoss );

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
			addImpact( RockImpactPtr( new RockImpact( enemy->getPos( ) + Vector( 0, 30, 0 ) ) ) );
			Sound::getTask( )->playSE( "yokai_se_26.wav" );
			//死んだ場合はドロップ
			if ( enemy->isDead( ) ) {
				enemy->dropItem( );
			}
			if ( !std::dynamic_pointer_cast< RockEnemyBoss >( enemy ) &&
				 !std::dynamic_pointer_cast< RockEnemyAttack >( enemy ) ) {
				enemy->reset( );
				_pops.push_back( RockPopPtr( new RockPop( enemy, false ) ) );
			}
			enemy->stopEffect( );
			ite = _enemies.erase( ite );
			continue;
		}

		enemy->update( );
		
		RockPlayerPtr overlapped_player = family->getOverLappedPlayer( enemy );
		if ( overlapped_player ) {
			RockEnemyBossPtr boss = std::dynamic_pointer_cast< RockEnemyBoss >( enemy );
			if ( !boss ) {
				enemy->adjustPosForOverLapped( overlapped_player );
			}
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
		pop->update( );
		if ( pop->isFinished( ) ) {
			ite = _pops.erase( ite );
			continue;
		}
		ite++;
	}
}

void RockMilitary::addEnemy( RockEnemyPtr enemy ) {
	_enemies.push_back( enemy );
}

void RockMilitary::addPop( RockPopPtr pop ) {
	_pops.push_back( pop );
}

void RockMilitary::addImpact( RockImpactPtr impact ) {
	_impacts.push_back( impact );
}

void RockMilitary::clean( ) {
	{
		std::list< RockEnemyPtr >::iterator ite = _enemies.begin( );
		while ( ite != _enemies.end( ) ) {
			RockEnemyPtr enemy = *ite;
			enemy->stopEffect( );
			enemy.reset( );
			ite++;
		}
		_enemies = { };
	}
	{
		std::list< RockImpactPtr >::iterator ite = _impacts.begin( );
		while ( ite != _impacts.end( ) ) {
			RockImpactPtr impact = *ite;
			impact.reset( );
			ite++;
		}
		_impacts = { };
	}
	{
		std::list< RockPopPtr >::iterator ite = _pops.begin( );
		while ( ite != _pops.end( ) ) {
			RockPopPtr pop = *ite;
			pop.reset( );
			ite++;
		}
		_pops = { };
	}
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