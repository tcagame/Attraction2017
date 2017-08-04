#include "RockCharacter.h"
#include "RockMilitary.h"
#include "RockMap.h"
#include "RockDollHouse.h"

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
