#include "RockMilitary.h"
#include "Application.h"
#include "Drawer.h"
#include "RockEnemy.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockImpact.h"
#include "define.h"
#include "Effect.h"

RockMilitaryPtr RockMilitary::getTask( ) {
	return std::dynamic_pointer_cast< RockMilitary >( Application::getInstance( )->getTask( getTag( ) ) );
}


RockMilitary::RockMilitary( ) {
}


RockMilitary::~RockMilitary( ) {
}

void RockMilitary::initialize( ) {
	EffectPtr effect( Effect::getTask( ) );
	effect->loadEffect( EFFECT_IMPACT, "effect/impact.efk" );
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
			ite = _enemies.erase( ite );
			continue;
		}

		enemy->update( );
		//player‚Æ‚Ì“–‚½‚è”»’è
		for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
			RockPlayerPtr player = family->getPlayer( i );
			if ( player->isActive( ) && player->isOverLapped( enemy ) ) {
				if ( player->isOnHead( enemy ) ) {
					player->bound( );
				} else {
					int force = -enemy->getForce( );
					player->damage( force );
					player->back( );
				}
			}
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

void RockMilitary::add( RockEnemyPtr enemy ) {
	_enemies.push_back( enemy );
}

void RockMilitary::add( RockImpactPtr impact ) {
	_impacts.push_back( impact );
}
