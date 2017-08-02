#include "RockCharacter.h"
#include "RockMilitary.h"
#include "RockMap.h"
#include "RockDollHouse.h"

RockCharacter::RockCharacter( const Vector& pos, DOLL id, bool mass ) :
_pos( pos ),
_id( id ),
_mass( mass ) {
}


RockCharacter::~RockCharacter( ) {
}

void RockCharacter::update( ) {
	ModelMV1Ptr map_model = RockMap::getTask( )->getModel( );
	act( );
	if ( _mass ) {
		//—Ž‰º
		_vec.y += GRAVITY;
	}
	if ( map_model->isHitLine( _pos, _pos + _vec ) ) {
		_vec = Vector( );
	}
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

DOLL RockCharacter::getId( ) const {
	return _id;
}