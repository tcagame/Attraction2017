#include "Armoury.h"
#include "Shot.h"
#include "Application.h"
#include <assert.h>
#include "Military.h"
#include "Enemy.h"
#include "Impact.h"

ArmouryPtr Armoury::getTask( ) {
	return std::dynamic_pointer_cast< Armoury >( Application::getInstance( )->getTask( getTag( ) ) );
}

Armoury::Armoury( ) :
_shot_id( 0 ) {
}

Armoury::~Armoury( ) {
}

void Armoury::update( ) {
	MilitaryPtr militari( Military::getTask( ) );
	std::array< ShotPtr, MAX_SHOT_NUM >::iterator ite = _shot_list.begin( );
	while ( ite != _shot_list.end( ) ) {
		ShotPtr shot = (*ite);
		if ( !shot ) {
			ite++;
			continue;
		}
		shot->update( );
		EnemyPtr hit_enemy = militari->getOverLappedEnemy( shot );
		if ( hit_enemy ) {
			hit_enemy->damage( 1 );
			if ( hit_enemy->isFinished( ) ) {
				_impacts.push_back( ImpactPtr( new Impact( shot->getPos( ) ) ) );
			}
		}
		ite++;
	}
}

ShotConstPtr Armoury::getShot( int idx ) const {
	assert( idx < MAX_SHOT_NUM );
	assert( idx >= 0 );
	return _shot_list[ idx ];
}

int Armoury::getMaxShotNum( ) const {
	return MAX_SHOT_NUM;
}

void Armoury::add( ShotPtr shot ) {
	_shot_list[ _shot_id ] = shot;
	_shot_id++;
	_shot_id %= MAX_SHOT_NUM;
}