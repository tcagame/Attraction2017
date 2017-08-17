#include "RockCharacter.h"
#include "RockMilitary.h"
#include "RockMap.h"
#include "RockDollHouse.h"

#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockMilitary.h"
#include "RockEnemy.h"

const double BOUND_POWER = 1.0;

RockCharacter::RockCharacter( const Vector& pos, DOLL doll, int radius, int height, bool mass, bool head ) :
_pos( pos ),
_doll( doll ),
_mass( mass ),
_act_count( 0 ),
_radius( radius ),
_height( height ),
_head( head ),
_dir( ( ( _pos + _vec ) - _pos ).normalize( ) ) {
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
	Vector dir = ( ( _pos + _vec ) - _pos ).normalize( );
	if ( dir.getLength2( ) > 0.5 ) {
		_dir = dir;
	}
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

Vector RockCharacter::getDir( ) const {
	return _dir;
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

bool RockCharacter::isHead( ) const {
	return _head;
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

int RockCharacter::getHeight( ) const {
	return _height;
}

void RockCharacter::damage( int force ) {
}

void RockCharacter::bound( ) {
	_vec.y = BOUND_POWER;
}

bool RockCharacter::isOnHead( RockCharacterConstPtr target ) const {
	if ( _vec.y >= 0 ) {
		//上方向に動いてる
		return false;
	}
	if ( !target->isHead( ) ) {
		//相手の頭に乗ることが出来ない
		return false;
	}
	if ( target->getPos( ).y + target->getHeight( ) / 2 > getPos( ).y ) {
		return false;
	}
	return true;
}


bool RockCharacter::isOverLapped( RockCharacterConstPtr target ) const {
	bool result = false;

	Vector distance = target->getPos( ) - _pos;
	double distance_y = fabs( distance.y );
	distance.y = 0;

	double length = distance.getLength2( );
	double range_hol = target->getRadius( ) + getRadius( );
	double range_vir = target->getHeight( ) + getHeight( );
	if ( length < range_hol * range_hol ) {
		if ( distance_y < range_vir ) {
			result = true;
		}
	}
	return result;
}

void RockCharacter::back( ) {
	_pos -= _vec;
}
