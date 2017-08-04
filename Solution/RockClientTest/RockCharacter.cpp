#include "RockCharacter.h"
#include "RockMilitary.h"
#include "RockMap.h"
#include "RockDollHouse.h"

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
		//—Ž‰º
		_vec.y += GRAVITY;
	}
	{//…•½ˆÚ“®‚Å‚«‚é‚©‚Ç‚¤‚©
		//“ª
		Vector head = _pos + _vec + Vector( 0, _radius * 2, 0 );
		//‘«Œ³
		Vector leg = _pos + _vec;

		//“ª‚ÌˆÊ’u‚Å‚ ‚½‚é||‘«Œ³‚ª‚È‚¢
		if ( map_model->isHitLine( head, head - Vector( 0, _radius, 0 ) ) ||
			 !map_model->isHitLine( leg, leg + Vector( 0, _radius, 0 ) ) ) {
			_vec.x = 0;
			_vec.z = 0;
		}
	}
	{//ã‰º”»’è
		Vector fpos = _pos + Vector( 0, _vec.y, 0 );
		if ( map_model->isHitLine( _pos, fpos ) ) {
			_vec.y = 0;
			_standing = true;
		}
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

void RockCharacter::setRadius( int radius ) {
	_radius = radius;
}
