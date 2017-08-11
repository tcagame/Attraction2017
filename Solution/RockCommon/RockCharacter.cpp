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
		//—Ž‰º
		_vec.y += GRAVITY;
	}
	{//…•½ˆÚ“®‚Å‚«‚é‚©‚Ç‚¤‚©
		//“ª
		Vector head = _pos + _vec + Vector( 0, _radius * 2, 0 );
		//‘«Œ³
		Vector leg = _pos + _vec + Vector( 0, -GRAVITY * 2, 0 );

		//“ª‚ÌˆÊ’u‚Å‚ ‚½‚é
		if ( map_model->isHitLine( head, head - Vector( 0, _radius, 0 ) ) ) {
			_vec.x = 0;
			_vec.z = 0;
		}
		//‘«Œ³‚ª‚È‚¢
		if ( !map_model->isHitLine( leg, leg + Vector( 0, -100, 0 ) ) ) {
			_vec.x = 0;
			_vec.z = 0;
		}
	}
	{//ã‰º”»’è
		Vector pos = _pos + Vector( 0, -GRAVITY * 2, 0 );
		Vector fpos = _pos + Vector( 0, _vec.y, 0 );
		if ( map_model->isHitLine( pos, fpos ) ) {
			_vec.y = 0;
			_standing = true;
		}
	}
	{//‰¡”»’è
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
	// player ‚ ‚½‚è”»’è
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		RockPlayerPtr target = RockFamily::getTask( )->getPlayer( i );
		if ( ( target->getPos( ) - _pos ).getLength2( ) < 1 ) {
			continue; // Ž©•ª‚¾‚Á‚½‚ç”»’è‚µ‚È‚¢
		}
		if ( ( target->getPos( ) - _pos ).getLength2( ) > COLLISION_RANGE * COLLISION_RANGE ) {
			continue; // —£‚ê‚Ä‚¢‚½‚ç”»’è‚µ‚È‚¢
		}

		double range = target->getRadius( ) + _radius;
		{//ã‰º”»’è
			Vector diff = target->getPos( ) - ( _pos + Vector( 0, _vec.y, 0 ) );
			if ( diff.getLength2( ) < range * range ) {
				_vec.y = 0;
			}
		}
		{//‰¡”»’è
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
