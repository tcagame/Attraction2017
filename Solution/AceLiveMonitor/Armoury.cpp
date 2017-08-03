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
	for ( int i = 0; i < MAX_SHOT_NUM; i ++ ) {
		if ( !_shot_list[ i ] ) {
			continue;
		}
		if ( _shot_list[ i ]->isFinished( ) ) {
			_shot_list[ i ] = ShotPtr( );
			continue;
		}
		_shot_list[ i ]->update( );
		EnemyPtr hit_enemy = militari->getOverLappedEnemy( _shot_list[ i ] );
		if ( hit_enemy ) {
			hit_enemy->damage( _shot_list[ i ]->getPower( ) );
			if ( hit_enemy->isFinished( ) ) {
				Vector impact_pos = hit_enemy->getPos( );
				impact_pos.y += NORMAL_CHAR_GRAPH_SIZE / 2;
				_impacts.push_back( ImpactPtr( new Impact( impact_pos, _shot_list[ i ]->getState( ) ) ) );
				_shot_list[ i ] = ShotPtr( );
			}
		}
	}
	updateImpact( );
}

void Armoury::updateImpact( ) {
	std::list< ImpactPtr >::iterator ite = _impacts.begin( );
	while ( ite != _impacts.end( ) ) {
		ImpactPtr impact = (*ite);
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

std::list< ImpactPtr > Armoury::getImpactList( ) const {
	return _impacts;
}
