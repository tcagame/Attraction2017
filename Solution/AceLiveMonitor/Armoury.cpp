#include "Armoury.h"
#include "Shot.h"
#include "Application.h"
#include <assert.h>
#include "Military.h"
#include "Enemy.h"
#include "Impact.h"
#include "Magazine.h"
#include "SynchronousData.h"
#include "Family.h"

ArmouryPtr Armoury::getTask( ) {
	return std::dynamic_pointer_cast< Armoury >( Application::getInstance( )->getTask( getTag( ) ) );
}

Armoury::Armoury( ) :
_shot_id( 0 ) {
}

Armoury::~Armoury( ) {
}

void Armoury::update( ) {
	updateEnemy( );
}

void Armoury::updateEnemy( ) {
	MilitaryPtr militari( Military::getTask( ) );
	int camera_pos = ( int )Family::getTask( )->getCameraPos( );
	for ( int i = 0; i < MAX_SHOT_NUM; i ++ ) {
		if ( !_shot_list[ i ] ) {
			continue;
		}
		if ( _shot_list[ i ]->isFinished( ) ) {
			_shot_list[ i ] = ShotPtr( );
			continue;
		}
		_shot_list[ i ]->update( );
		_shot_list[ i ]->setSynchronousData( SynchronousData::TYPE_SHOT, camera_pos );
		EnemyPtr hit_enemy = militari->getOverlappedEnemy( _shot_list[ i ] );
		if ( hit_enemy ) {
			hit_enemy->damage( _shot_list[ i ]->getPower( ) );
			if ( !hit_enemy->isFinished( ) ) {
				//エネミーが倒れなかったらショットが当たった位置で爆発
				Vector impact_pos = _shot_list[ i ]->getPos( );
				impact_pos.y += NORMAL_CHAR_GRAPH_SIZE / 2;
				Magazine::getTask( )->add( ImpactPtr( new Impact( impact_pos, _shot_list[ i ]->getArea( ), 64 ) ) );
				_shot_list[ i ] = ShotPtr( );
			}
		}
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


