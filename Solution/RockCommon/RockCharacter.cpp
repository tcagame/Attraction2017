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
_mass( mass ),
_act_count( 0 ),
_doll( doll ),
_radius( radius ),
_height( height ),
_head( head ),
_dir( Vector( 0, 0, -1 ) ) {
}


RockCharacter::~RockCharacter( ) {
}

void RockCharacter::update( ) {
	std::vector< ModelMV1Ptr > col_models = RockMap::getTask( )->getColModels( );
	int col_models_size = ( int )col_models.size( );
	act( );
	_act_count++;
	_standing = false;
	if ( _mass ) {
		//����
		_vec.y += GRAVITY;
	}

	//�����ړ��ł��邩�ǂ���
	{
		Vector vec = Vector( _vec.x, 0, _vec.z );
		if ( vec.getLength2( ) > 0 ) {
			Vector central_pos = _pos + vec + Vector( 0, _radius, 0 );

			for ( int i = 0; i < col_models_size; i++ ) {
				//���̈ʒu�ł�����( pos1:���S�Apos2:�� )
				if ( col_models[ i ]->isHitLine( central_pos, central_pos + Vector( 0, _radius, 0 ) ) ) {
					_vec.x = 0;
					_vec.z = 0;
					break;
				}
				//�������Ȃ�( pos1:���S�Apos2:������菭�����̈ʒu )
				Vector hit_pos = col_models[ i ]->getHitPos( central_pos, central_pos - Vector( 0, _radius * 2, 0 ) );
				if ( hit_pos.isOrijin( ) ) {
					_vec.x = 0;
					_vec.z = 0;
					break;
				} else {
					_vec.y = hit_pos.y - _pos.y + GRAVITY / 2;
				}
			}
			
		}
	}
	{//�㉺����
		Vector pos = _pos + Vector( 0, -GRAVITY * 2, 0 );
		Vector fpos = _pos + Vector( 0, _vec.y, 0 );
		for ( int i = 0; i < col_models_size; i++ ) {
			if ( col_models[ i ]->isHitLine( pos, fpos ) ) {
				_vec.y = 0;
				_standing = true;
				break;
			}
		}
	}
	{//�����Ă�������o��
		Vector vec = Vector( _vec.x, 0, _vec.z );
		if ( vec.getLength2( ) > 0.5 ) {
			_dir = vec.normalize( );
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

Vector RockCharacter::getDir( ) const {
	return _dir;
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

DOLL RockCharacter::getDoll( ) const {
	return _doll;
}

void RockCharacter::setDoll( DOLL doll ) {
	_doll = doll;
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
		//������ɓ����Ă�
		return false;
	}
	if ( !target->isHead( ) ) {
		//����̓��ɏ�邱�Ƃ��o���Ȃ�
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
