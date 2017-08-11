#include "RockCharacter.h"
#include "RockMilitary.h"
#include "RockMap.h"
#include "RockDollHouse.h"

#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockMilitary.h"
#include "RockEnemy.h"



RockCharacter::RockCharacter( const Vector& pos, DOLL doll, bool mass ) :
_pos( pos ),
_doll( doll ),
_mass( mass ),
_act_count( 0 ),
_radius( 10 ) {
}


RockCharacter::~RockCharacter( ) {
}

void RockCharacter::update( ) {
	ModelMV1Ptr map_model = RockMap::getTask( )->getColModel( );
	act( );
	_act_count++;
	_standing = false;
	if ( _mass ) {
		//落下
		_vec.y += GRAVITY;
	}
	{//水平移動できるかどうか
		//頭
		Vector head = _pos + _vec + Vector( 0, _radius * 2, 0 );
		//足元
		Vector leg = _pos + _vec + Vector( 0, -GRAVITY * 2, 0 );

		//頭の位置であたる
		if ( map_model->isHitLine( head, head - Vector( 0, _radius, 0 ) ) ) {
			_vec.x = 0;
			_vec.z = 0;
		}
		//足元がない
		if ( !map_model->isHitLine( leg, leg + Vector( 0, -100, 0 ) ) ) {
			_vec.x = 0;
			_vec.z = 0;
		}
	}
	{//上下判定
		Vector pos = _pos + Vector( 0, -GRAVITY * 2, 0 );
		Vector fpos = _pos + Vector( 0, _vec.y, 0 );
		if ( map_model->isHitLine( pos, fpos ) ) {
			_vec.y = 0;
			_standing = true;
		}
	}
	{//横判定
		Vector fpos = _pos + Vector( _vec.x, 0, _vec.z );
		if ( map_model->isHitLine( _pos, fpos ) ) {
			_vec.x = 0;
			_vec.z = 0;
			_standing = true;
		}
	}
	collision( );
	_pos += _vec;
}

void RockCharacter::setVec( const Vector& vec ) {
	_vec = vec;
}

void RockCharacter::setPos( const Vector& pos ) {
	_pos = pos;
}

Vector RockCharacter::getVec( ) const {
	return _vec;
}

Vector RockCharacter::getPos( ) const {
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

void RockCharacter::setRadius( int radius ) {
	_radius = radius;
}

int RockCharacter::getRadius( ) const {
	return _radius;
}

void RockCharacter::collision( ) {
	// player あたり判定
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		RockPlayerPtr target = RockFamily::getTask( )->getPlayer( i );
		if ( ( target->getPos( ) - _pos ).getLength2( ) < 1 ) {
			continue; // 自分だったら判定しない
		}
		if ( ( target->getPos( ) - _pos ).getLength2( ) > COLLISION_RANGE * COLLISION_RANGE ) {
			continue; // 離れていたら判定しない
		}

		double range = target->getRadius( ) + _radius;
		{//上下判定
			Vector diff = target->getPos( ) - ( _pos + Vector( 0, _vec.y, 0 ) );
			if ( diff.getLength2( ) < range * range ) {
				_vec.y = 0;
			}
		}
		{//横判定
			Vector diff = target->getPos( ) - ( _pos + Vector( _vec.x, 0, _vec.z ) );
			if ( diff.getLength2( ) < range * range ) {
				_vec.x = 0;
				_vec.z = 0;
			}
		}
	}
}

void RockCharacter::damage( int force ) {
}
