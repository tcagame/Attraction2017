#include "RockMilitary.h"
#include "Application.h"
#include "RockEnemy.h"
#include "RockEnemyGhost.h"
#include "RockEnemyRedBard.h"

RockMilitaryPtr RockMilitary::getTask( ) {
	return std::dynamic_pointer_cast< RockMilitary >( Application::getInstance( )->getTask( getTag( ) ) );
}


RockMilitary::RockMilitary( ) {
	_enemies.push_back( RockEnemyPtr( new RockEnemyGhost( Vector( 0, 30, 0 ) ) ) );
	_enemies.push_back( RockEnemyPtr( new RockEnemyRedBard( Vector( 0, 30, 0 ) ) ) );
}


RockMilitary::~RockMilitary( ) {
}

std::list< RockEnemyPtr > RockMilitary::getEnemyList( ) const {
	return _enemies;
}

void RockMilitary::update( ) {
	std::list< RockEnemyPtr >::iterator ite = _enemies.begin( );
	while ( ite != _enemies.end( ) ) {
		RockEnemyPtr enemy = (*ite);
		if ( !enemy ) {
			ite++;
			continue;
		}
		enemy->update( );
		ite++;
	}
}