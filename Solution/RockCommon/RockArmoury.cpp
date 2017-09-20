#include "RockArmoury.h"
#include "Application.h"
#include "Drawer.h"
#include "define.h"
#include "RockShot.h"
#include "RockMilitary.h"
#include "RockEnemy.h"
#include <list>
#include "Effect.h"
#include "RockShotPlayer.h"
#include "Sound.h"

RockArmouryPtr RockArmoury::getTask( ) {
	return std::dynamic_pointer_cast< RockArmoury >( Application::getInstance( )->getTask( getTag( ) ) );
}


RockArmoury::RockArmoury( ) {
}

RockArmoury::~RockArmoury( ) {
}

void RockArmoury::initialize( ) {
}

void RockArmoury::update( ) {
	std::list< RockShotPtr >::iterator ite = _shots.begin( );
	while( ite != _shots.end( ) ) {
		RockShotPtr shot = *ite;
		if ( !shot ) {
			ite++;
			continue;
		}
		if ( shot->isFinished( ) ) {
			shot->stopEffect( );
			ite = _shots.erase( ite );
			continue;
		}
		shot->update( );
		RockEnemyPtr enemy = getOverLappedEnemy( shot );
		if ( enemy ) {
			Sound::getTask( )->playSE( "yokai_se_25.wav" );
			enemy->damage( shot->getPower( ) );
			RockShotPlayerPtr player_shot = std::dynamic_pointer_cast< RockShotPlayer >( shot );
			if ( player_shot ) {
				player_shot->setBack( );
			}
		}
		ite++;
	}
}

std::list< RockShotPtr > RockArmoury::getShots( ) const {
	return _shots;
}

void RockArmoury::addShot( RockShotPtr shot ) {
	_shots.push_back( shot );
}

RockEnemyPtr RockArmoury::getOverLappedEnemy( RockShotPtr shot ) const {
	RockEnemyPtr result = RockEnemyPtr( );
	std::list< RockEnemyPtr > enemies = RockMilitary::getTask( )->getEnemyList( );
	std::list< RockEnemyPtr >::iterator ite = enemies.begin( );
	while ( ite != enemies.end( ) ) {
		RockEnemyPtr enemy = *ite;
		if ( !enemy ) {
			ite++;
			continue;
		}
		if ( shot->isOverLapped( enemy ) ) {
			result = enemy;
			break;
		}
		ite++;
	}
	return result;
}

void RockArmoury::clearShot( ) {
	std::list< RockShotPtr >::const_iterator ite = _shots.begin( );
	while ( ite != _shots.end( ) ) {
		RockShotPtr shot = *ite;
		if ( !shot ) {
			ite++;
			continue;
		}

		shot = RockShotPtr( );
		ite++;
	}
	_shots.clear( );
}
