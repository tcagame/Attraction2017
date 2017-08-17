#include "RockArmoury.h"
#include "Application.h"
#include "Drawer.h"
#include "define.h"
#include "RockShot.h"

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
	std::list< RockShotPtr >::iterator ite = _shots.begin( );
	while( ite != _shots.end( ) ) {
		RockShotPtr shot = *ite;
		if ( !shot ) {
			ite++;
			continue;
		}
		if ( shot->isfinished( ) ) {
			ite = _shots.erase( ite );
			continue;
		} else {
			shot->update( );
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
