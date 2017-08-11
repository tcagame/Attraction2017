#include "RockMilitary.h"
#include "Application.h"
#include "RockEnemy.h"
#include "RockFamily.h"
#include "RockPlayer.h"

RockMilitaryPtr RockMilitary::getTask( ) {
	return std::dynamic_pointer_cast< RockMilitary >( Application::getInstance( )->getTask( getTag( ) ) );
}


RockMilitary::RockMilitary( ) {
}


RockMilitary::~RockMilitary( ) {
}

std::list< RockEnemyPtr > RockMilitary::getEnemyList( ) const {
	return _enemies;
}

void RockMilitary::update( ) {
	std::list< RockEnemyPtr >::iterator ite = _enemies.begin( );
	RockFamilyPtr family( RockFamily::getTask( ) );
	while ( ite != _enemies.end( ) ) {
		RockEnemyPtr enemy = (*ite);
		if ( !enemy ) {
			ite++;
			continue;
		}
		for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
			RockPlayerPtr player = family->getPlayer( i );
			if ( player->isActive( ) && enemy->isOverRapped( player ) ) {
				if ( player->isOnHead( enemy ) ) {
					player->bound( );
				} else {
					int force = -enemy->getForce( );
					player->damage( force );
				}
			}
		}
		enemy->update( );
		ite++;
	}
}

void RockMilitary::add( RockEnemyPtr enemy ) {
	_enemies.push_back( enemy );
}
