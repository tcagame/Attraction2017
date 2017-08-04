#include "RockCharacter.h"
#include "RockMilitary.h"
#include "RockMap.h"
#include "RockDollHouse.h"

#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockMilitary.h"
#include "RockEnemy.h"

const int COLLISION_RANGE = 20;

RockCharacter::RockCharacter( const Vector& pos, DOLL doll, bool mass ) :
_pos( pos ),
_doll( doll ),
_mass( mass ),
_act_count( 0 ) {
}


RockCharacter::~RockCharacter( ) {
}

void RockCharacter::update( ) {
	ModelMV1Ptr map_model = RockMap::getTask( )->getModel( );
	act( );
	_act_count++;
	_standing = false;
	if ( _mass ) {
		//—Ž‰º
		_vec.y += GRAVITY;
	}
	if ( map_model->isHitLine( _pos, _pos + _vec ) ) {
		_vec = Vector( );
		_standing = true;
	}
	collision( );
	_pos += _vec;
}

void RockCharacter::setVec( const Vector& vec ) {
	_vec = vec;
}
Vector RockCharacter::getVec( ) const {
	return _vec;
}

Vector RockCharacter::getPos( ) {
	return _pos;
}

DOLL RockCharacter::getDoll( ) const {
	return _doll;
}

void RockCharacter::setDoll( DOLL doll ) {
	_doll = doll;
}

bool RockCharacter::isStanding( ) const {
	return _standing;
}

void RockCharacter::setActCount( int count ) {
	_act_count = count;
}

int RockCharacter::getActCount( ) const {
	return _act_count;
}

void RockCharacter::collision( ) {
	// player ‚ ‚½‚è”»’è
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		RockPlayerPtr player = RockFamily::getTask( )->getPlayer( i );
		if ( _doll == player->getDoll( ) ) {
			continue;
		}
		if ( ( player->getPos( ) - _pos ).getLength2( ) > COLLISION_RANGE * COLLISION_RANGE ) {
			continue;
		}

		ModelMV1Ptr target = RockDollHouse::getTask( )->getModel( player->getDoll( ) );
		if ( target->isHitLine( _pos, _pos + _vec ) ) {
			_vec = Vector( );
			return;
		}
	}

	// enemy ‚ ‚½‚è”»’è
	std::list< RockEnemyPtr > enemys = RockMilitary::getTask( )->getEnemyList( );
	std::list< RockEnemyPtr >::iterator ite = enemys.begin( );

	while ( ite != enemys.end( ) ) {
		if ( !( *ite ) ) {
			ite++;
			continue;
		}
		RockEnemyPtr enemy = ( *ite );

		if ( _doll == enemy->getDoll( ) ) {
			ite++;
			continue;
		}
		if ( ( enemy->getPos( ) - _pos ).getLength2( ) > COLLISION_RANGE * COLLISION_RANGE ) {
			ite++;
			continue;
		}

		ModelMV1Ptr target = RockDollHouse::getTask( )->getModel( enemy->getDoll( ) );
		if ( target->isHitLine( _pos, _pos + _vec ) ) {
			_vec = Vector( );
			return;
		}
		ite++;
	}
}