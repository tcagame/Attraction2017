#include "RockArmoury.h"
#include "Application.h"
#include "Drawer.h"
#include "define.h"
#include "RockShot.h"
#include "RockMilitary.h"
#include "RockEnemy.h"
#include <list>

RockArmouryPtr RockArmoury::getTask( ) {
	return std::dynamic_pointer_cast< RockArmoury >( Application::getInstance( )->getTask( getTag( ) ) );
}


RockArmoury::RockArmoury( ) {
}

RockArmoury::~RockArmoury( ) {
}

void RockArmoury::initialize( ) {
	Drawer::getTask( )->loadEffect( EFFECT_SHOT, "effect/laser.efk" );
}

void RockArmoury::update( ) {
	std::list< RockShotPtr >::iterator shot_ite = _shots.begin( );
	while( shot_ite != _shots.end( ) ) {
		RockShotPtr shot = *shot_ite;
		if ( !shot ) {
			shot_ite++;
			continue;
		}
		if ( shot->isFinished( ) ) {
			shot_ite = _shots.erase( shot_ite );
			continue;
		}

		shot->update( );
		std::list< RockEnemyPtr > enemies = RockMilitary::getTask( )->getEnemyList( );
		std::list< RockEnemyPtr >::iterator ene_ite = enemies.begin( );
		while ( ene_ite != enemies.end( ) ) {
			RockEnemyPtr enemy = *ene_ite;
			if ( !enemy ) {
				ene_ite++;
				continue;
			}

			if ( shot->isOverLapped( enemy ) ) {
				enemy->damage( 1 );
				shot->setBack( );
				break;
			}
			ene_ite++;
		}
		shot_ite++;
	}
}

std::list< RockShotPtr > RockArmoury::getShots( ) const {
	return _shots;
}

void RockArmoury::addShot( RockShotPtr shot ) {
	_shots.push_back( shot );
}
