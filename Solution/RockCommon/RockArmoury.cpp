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

RockArmouryPtr RockArmoury::getTask( ) {
	return std::dynamic_pointer_cast< RockArmoury >( Application::getInstance( )->getTask( getTag( ) ) );
}


RockArmoury::RockArmoury( ) {
}

RockArmoury::~RockArmoury( ) {
}

void RockArmoury::initialize( ) {
	EffectPtr effect( Effect::getTask( ) );
	_shot_id = effect->loadEffect( EFFECT_SHOT, "shot.efk" );
	_charge_shot_id = effect->loadEffect( EFFECT_CHARGE_SHOT, "charge_shot.efk" );
	_charge_id = effect->loadEffect( EFFECT_CHARGE, "charge.efk" );
}

int RockArmoury::getEffectShotId( ) const {
	return _shot_id;
}

int RockArmoury::getEffectChargeId( ) const {
	return _charge_id;
}

int RockArmoury::getEffectChageShotId( ) const {
	return _charge_shot_id;	
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
			ite = _shots.erase( ite );
			continue;
		}
		shot->update( );
		RockEnemyPtr enemy = getOverLappedEnemy( shot );
		if ( enemy ) {
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
