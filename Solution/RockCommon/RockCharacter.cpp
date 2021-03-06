#include "RockCharacter.h"
#include "RockMilitary.h"
#include "RockMap.h"
#include "RockDollHouse.h"

#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockMilitary.h"
#include "RockEnemy.h"
#include "RockShadow.h"

const double BOUND_POWER = 5.0;
const double STAND_RANGE = 1000.0;
const double DRAW_SHADOW_RANGE = 500.0;

RockCharacter::RockCharacter( const Vector& pos, DOLL doll, int radius, int height, bool mass, bool head, bool col, bool shadow ) :
_pos( pos ),
_mass( mass ),
_act_count( 0 ),
_doll( doll ),
_radius( radius ),
_height( height ),
_head( head ),
_col( col ),
_shadow( shadow ),
_standing( false ),
_dir( Vector( 0, 0, -1 ) ) {
}


RockCharacter::~RockCharacter( ) {
}

void RockCharacter::update( ) {
	act( );
	updateInCamera( );
	_act_count++;
	_standing = false;
	if ( _mass ) {
		//落下
		_vec.y += GRAVITY;
	}

	//水平移動できるかどうか
	if ( _col ) {
		Vector vec = Vector( _vec.x, 0, _vec.z );
		if ( vec.getLength2( ) > 0 ) {
			if ( !isOnMapModel( Vector( _vec.x, 0, _vec.z ) ) ) {
				_vec.x = 0;
				_vec.z = 0;
			}
		}
	}

	std::vector< ModelMV1Ptr > col_models = RockMap::getTask( )->getColModels( );
	int col_models_size = ( int )col_models.size( );
	if ( _col ) {//上下判定
		Vector pos = _pos + Vector( 0, _radius * 2, 0 );
		Vector fpos = _pos + Vector( 0, _vec.y, 0 );
		for ( int i = 0; i < col_models_size; i++ ) {
			if ( col_models[ i ]->isHitLine( pos, fpos ) ) {
				_pos.y = col_models[ i ]->getHitPos( ).y - GRAVITY / 2;
				_vec.y = 0;
				_standing = true;
				break;
			}
		}
	}
	{//向いてる方向を出す
		Vector vec = Vector( _vec.x, 0, _vec.z );
		if ( vec.getLength2( ) > 0.1 ) {
			_dir = vec.normalize( );
		}
	}
	_pos += _vec;
	Vector diff = RockFamily::getTask( )->getCameraPos( ) - _pos;
	if ( _shadow && 
		 diff.getLength2( ) < DRAW_SHADOW_RANGE * DRAW_SHADOW_RANGE ) {
		RockShadowPtr shadow = RockShadow::getTask( );
		if( shadow ){
			shadow->set( getPos( ), getOverlappedRadius( ) );
		}
	}
}

void RockCharacter::setVec( const Vector& vec ) {
	_vec = vec;
}

void RockCharacter::setPos( const Vector& pos ) {
	_pos = pos;
}

void RockCharacter::setDir( const Vector& dir ) {
	_dir = dir;
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

void RockCharacter::setOverlappedRadius( int radius ) {
	_radius = radius;
}

DOLL RockCharacter::getDoll( ) const {
	return _doll;
}

void RockCharacter::setDoll( DOLL doll ) {
	_doll = doll;
}

int RockCharacter::getOverlappedRadius( ) const {
	return _radius;
}

int RockCharacter::getHeight( ) const {
	return _height;
}

void RockCharacter::setMass( bool mass ) {
	_mass = mass;
}

void RockCharacter::setCol( bool col ) {
	_col = col;
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

	Vector self = getPos( ) + Vector( 0, getHeight( ), 0 );
	Vector own = target->getPos( ) + Vector( 0, target->getHeight( ), 0 );
	Vector diff = own - self;
	double range_hol = target->getOverlappedRadius( ) + getOverlappedRadius( );
	if ( diff.getLength2( ) < range_hol * range_hol ) {
		result = true;
	}
	return result;
}

void RockCharacter::back( ) {
	_pos -= _vec;
}

bool RockCharacter::isOnMapModel( const Vector& vec ) const {
	bool result = true;
	std::vector< ModelMV1Ptr > col_models = RockMap::getTask( )->getColModels( );
	int col_models_size = ( int )col_models.size( );
	Vector central_pos = _pos + vec + Vector( 0, _radius, 0 );

	for ( int i = 0; i < col_models_size; i++ ) {
		//頭の位置であたる( pos1:中心、pos2:頭 )
		if ( col_models[ i ]->isHitLine( central_pos, central_pos + Vector( 0, _radius, 0 ) ) ) {
			result = false;
			break;
		}
		//足元がない( pos1:中心、pos2:結構下のほう )
		if ( !col_models[ i ]->isHitLine( central_pos, central_pos - Vector( 0, STAND_RANGE, 0 ) ) ) {
			result = false;
			break;
		}
	}	
	return result;
}

void RockCharacter::adjustPosForOverLapped( RockPlayerPtr target ) {
	Vector target_pos = target->getPos( );
	Vector distance = target_pos - _pos;
	Vector pos = target_pos - distance.normalize( ) * ( target->getOverlappedRadius( ) + _radius - 1 );
	Vector vec = pos - _pos;
	if ( distance.y > 0 ) {
		vec.y = -distance.y;
	} else {
		vec.y = 0;
	}
	if( isOnMapModel( vec ) ) {
		_pos = _pos + vec;
	}
}

void RockCharacter::adjustPosForOverLapped( RockEnemyPtr target ) {
	Vector target_pos = target->getPos( );
	Vector distance = target_pos - _pos;
	Vector pos = target_pos - distance.normalize( ) * ( target->getOverlappedRadius( ) + _radius - 1 );
	Vector vec = pos - _pos;
	vec.y = 0;
	if( isOnMapModel( vec ) ) {
		_pos = _pos + vec;
	}
}
