#include "RockArmoury.h"
#include "Application.h"
#include "Drawer.h"
#include "define.h"
#include "RockShot.h"
#include "RockMilitary.h"
#include "RockEnemy.h"
#include <list>
#include "Effect.h"

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
	_charge_id = effect->loadEffect( EFFECT_CHARGE, "charge.efk" );
}

int RockArmoury::getEffectShotId( ) const {
	return _shot_id;
}

int RockArmoury::getEffectChargeId( ) const {
	return _charge_id;
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
				enemy->damage( shot->getPower( ) );
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
