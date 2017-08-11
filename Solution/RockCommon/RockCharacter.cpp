#include "RockCharacter.h"
#include "RockMilitary.h"
#include "RockMap.h"
#include "RockDollHouse.h"

#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockMilitary.h"
#include "RockEnemy.h"

const double BOUND_POWER = 1.0;

RockCharacter::RockCharacter( const Vector& pos, DOLL doll, int radius, bool mass, bool head ) :
_pos( pos ),
_doll( doll ),
_mass( mass ),
_act_count( 0 ),
_radius( radius ),
_head( head ) {
}


RockCharacter::~RockCharacter( ) {
}

void RockCharacter::update( ) {
	ModelMV1Ptr map_model = RockMap::getTask( )->getColModel( );
	act( );
	_act_count++;
	_standing = false;
	if ( _mass ) {
		//����
		_vec.y += GRAVITY;
	}
	{//�����ړ��ł��邩�ǂ���
		//��
		Vector head = _pos + _vec + Vector( 0, _radius * 2, 0 );
		//����
		Vector leg = _pos + _vec + Vector( 0, -GRAVITY * 2, 0 );

		//���̈ʒu�ł�����
		if ( map_model->isHitLine( head, head - Vector( 0, _radius, 0 ) ) ) {
			_vec.x = 0;
			_vec.z = 0;
		}
		//�������Ȃ�
		if ( !map_model->isHitLine( leg, leg + Vector( 0, -100, 0 ) ) ) {
			_vec.x = 0;
			_vec.z = 0;
		}
	}
	{//�㉺����
		Vector pos = _pos + Vector( 0, -GRAVITY * 2, 0 );
		Vector fpos = _pos + Vector( 0, _vec.y, 0 );
		if ( map_model->isHitLine( pos, fpos ) ) {
			_vec.y = 0;
			_standing = true;
		}
	}
	{//������
		Vector fpos = _pos + Vector( _vec.x, 0, _vec.z );
		if ( map_model->isHitLine( _pos, fpos ) ) {
			_vec.x = 0;
			_vec.z = 0;
			_standing = true;
		}
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

void RockCharacter::damage( int force ) {
}

void RockCharacter::bound( ) {
	_vec.y = BOUND_POWER;
}

bool RockCharacter::isOnHead( RockCharacterConstPtr target ) const {
	if ( _vec.y >= 0 ) {
		return false;
	}
	if ( !target->isHead( ) ) {
		return false;
	}
	Vector target_pos = target->getPos( );
	double length = ( target_pos - _pos ).getLength2( );
	if ( length < 0.1 ) {
		// �����������画�肵�Ȃ�
		return false;
	}
	if ( length > COLLISION_RANGE * COLLISION_RANGE ) {
		// ����Ă����画�肵�Ȃ�
		return false;
	}
		
	double range = target->getRadius( ) + getRadius( );
	{//�㉺����
		Vector diff = target_pos - _pos;
		if ( diff.getLength2( ) > range * range ) {
			return false;
		}
	}
	return true;
}


bool RockCharacter::isOverRapped( RockCharacterConstPtr target ) const {
	bool result = false;
	Vector target_pos = target->getPos( );
		
	double length = ( target_pos - _pos ).getLength2( );
	if ( length < 0.1 ) {
		// �����������画�肵�Ȃ�
		return false;
	}
	if ( length > COLLISION_RANGE * COLLISION_RANGE ) {
		// ����Ă����画�肵�Ȃ�
		return false;
	}
	
	double range = target->getRadius( ) + getRadius( );
	{//�㉺����
		Vector diff = target_pos - _pos;
		if ( diff.getLength2( ) < range * range ) {
			result = true;
		}
	}
	{//������
		Vector diff = target_pos - _pos;
		if ( diff.getLength2( ) < range * range ) {
			result = true;
		}
	}
	return result;
}

void RockCharacter::back( ) {
	_pos -= _vec;
}
