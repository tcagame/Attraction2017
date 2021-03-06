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
#include "Player.h"
#include "EnemyGama.h"
#include "Sound.h"
#include "ShotPlayer.h"

PTR( EnemyGama );

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
	int camera_pos = Family::getTask( )->getCameraPosX( );
	for ( int i = 0; i < MAX_SHOT_NUM; i ++ ) {
		if ( !_shot_list[ i ] ) {
			continue;
		}
		if ( _shot_list[ i ]->isFinished( ) ) {
			_shot_list[ i ] = ShotPtr( );
			continue;
		}
		_shot_list[ i ]->update( );
		EnemyPtr hit_enemy = militari->getOverlappedEnemy( _shot_list[ i ] );
		if ( hit_enemy ) {
			ShotPlayerPtr shot_player = std::dynamic_pointer_cast< ShotPlayer >( _shot_list[ i ] );
			if ( shot_player ) {
				if ( shot_player->isNormal( ) ) {
					shot_player->erase( );
				}
			}
			hit_enemy->damage( _shot_list[ i ]->getPower( ) );
			if ( hit_enemy->getPower( ) > 0 ) {
				//エネミーが倒れなかったらショットが当たった位置で爆発
				Sound::getTask( )->playSE( "yokai_se_25.wav" );
				Vector impact_pos = _shot_list[ i ]->getPos( );
				Magazine::getTask( )->add( ImpactPtr( new Impact( impact_pos, _shot_list[ i ]->getArea( ), 64 ) ) );
				_shot_list[ i ]->erase( );
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
	_shot_id = ( _shot_id + 1 ) % MAX_SHOT_NUM;
}

void Armoury::pushDebugData( ViewerDebug::Data& data ) {
	for ( int i = 0; i < MAX_SHOT_NUM; i++ ) {
		if ( !_shot_list[ i ] ) {
			continue;
		}
		data.circle.push_back( _shot_list[ i ]->getDebugDataCircle( ) );
	}
}

void Armoury::eraseEventShot( ) {
	for ( int i = 0; i < MAX_SHOT_NUM; i++ ) {
		if ( !_shot_list[ i ] ) {
			continue;
		}
		if ( _shot_list[ i ]->getArea( ) == AREA_EVENT ) {
			_shot_list[ i ] = ShotPtr( );
		}
	}
}

void Armoury::setSynchronousData( ) {
	int camera_pos = Family::getTask( )->getCameraPosX( );
	for ( int i = 0; i < MAX_SHOT_NUM; i ++ ) {
		if ( !_shot_list[ i ] ) {
			continue;
		}
		if ( _shot_list[ i ]->isFinished( ) ) {
			continue;
		}
		_shot_list[ i ]->setSynchronousData( camera_pos );
	}
}

