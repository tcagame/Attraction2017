#include "Character.h"
#include "ace_define.h"
#include "Family.h"
#include "Player.h"
#include "World.h"
#include "Map.h"

const int MAX_SPEED_Y = 16;
const int MAX_ACT_COUNT = 0xfffffff;

Character::Character( const Vector& pos, const int chip_size, const int power, bool mass ) :
_pos( pos ),
_standing( false ),
_chip_size( chip_size ),
_act_count( 0 ),
_power( power ),
_mass( mass ),
_radius( chip_size / 2 ),
_finished( false ),
_area( AREA_STREET ) {
}


Character::~Character( ) {
}

void Character::update( ) {
	act( );

	_act_count = ( _act_count + 1 ) % MAX_ACT_COUNT;
	_standing = false;

	updateMass( );
	updateDir( );

	_pos += _vec;

}

void Character::updateMass( ) {
	if ( !_mass ) {
		return;
	}

	_vec.y += GRAVITY;

	if ( _vec.y > MAX_SPEED_Y ) {
		_vec.y = MAX_SPEED_Y;
	}
	if ( _vec.y < -MAX_SPEED_Y ) {
		_vec.y = -MAX_SPEED_Y;
	}
	MapPtr map = World::getTask( )->getMap( _area );
	//è„
	if ( _vec.y < 0 ) {
		unsigned char obj = map->getObject( _pos + Vector( 0, _vec.y - _radius * 2 ) );
		if ( obj == OBJECT_BLOCK ) {
			_pos.y = ( ( int )( _pos.y + _vec.y - _radius * 2 ) / OBJECT_CHIP_SIZE + 1 ) * OBJECT_CHIP_SIZE - GRAVITY / 2 + _radius * 2;
			_vec.y = 0;
		}
	}
	//â∫
	if ( _vec.y > 0 ) {
		unsigned char obj = map->getObject( _pos + Vector( 0, _vec.y ) );
		if ( obj == OBJECT_BLOCK ||
				obj == OBJECT_ONEWAY ) {
			_standing = true;
			_pos.y = ( ( int )( _pos.y + _vec.y ) / OBJECT_CHIP_SIZE ) * OBJECT_CHIP_SIZE - GRAVITY / 2;
			_vec.y = 0;
		}
	}
	//ç∂ë§
	if ( _vec.x < 0 ) {
		if ( map->getObject( _pos + Vector( _vec.x - _radius, 0 ) ) == OBJECT_BLOCK ) {
			_pos.x = ( ( int )( _pos.x + _vec.x - _radius ) / OBJECT_CHIP_SIZE + 1 ) * OBJECT_CHIP_SIZE + _radius;
			_vec.x = 0;
			_dir = DIR_LEFT;
		}
	}
	//âEë§
	if ( _vec.x > 0 ) {
		if ( map->getObject( _pos + Vector( _vec.x + _radius, 0 ) ) == OBJECT_BLOCK ) {
			_pos.x = ( ( int )( _pos.x + _vec.x + _radius ) / OBJECT_CHIP_SIZE ) * OBJECT_CHIP_SIZE - _radius;
			_vec.x = 0;
			_dir = DIR_RIGHT;
		}
	}
}

void Character::damage( int force ) {
	// ë¶éÄÇ…Ç≥ÇπÇÈ
	if ( force < 0 ) {
		force = _power;
	}

	// çUåÇóÕï™å∏ÇÁÇ∑
	_power -= force;
	if ( _power < 0 ) {
		_power = 0;
	}

	// éÄÇÒÇæÇ©ÅH
	if ( _power <= 0 ) {
		_finished = true;
	}
}


DIR Character::getDir( ) const {
	 return _dir;
}

Vector Character::getVec( ) const{
	return _vec;
}

Vector Character::getPos( ) const{
	return _pos;
}

void  Character::setVec( const Vector& vec ) {
	_vec = vec;
}

void  Character::setPos( const Vector& pos ) {
	_pos = pos;
}

void Character::setDir( DIR dir ) {
	_dir = dir;
}

int Character::getPower( ) const {
	return _power;
}

bool Character::isStanding( ) const {
	return _standing;
}

bool Character::isFinished( ) const {
	return _finished;
}

AREA Character::getArea( ) const {
	return _area;
}

void Character::updateDir( ) {
	if ( _vec.x < 0 ) {
		_dir = DIR_LEFT;
	}
	if ( _vec.x > 0 ) {
		_dir = DIR_RIGHT;
	}
}

int Character::getActCount( ) const {
	return _act_count;
}

int Character::getChipSize( ) const {
	return _chip_size;
}

bool Character::isOverlapped( CharacterConstPtr target ) const {
	if ( _area != target->getArea( ) ||
		 _finished ) {
		return false;
	}
	Vector self = _pos + Vector( 0, getChipSize( ) / 2 );
	Vector nonself = target->getPos( ) + Vector( 0, target->getChipSize( ) / 2 );
	double length = ( self - nonself ).getLength( );
	double radius = _radius + target->getRadius( );
	return ( length < radius );
}

void Character::setRadius( int radius ) {
	_radius = radius;
}

double Character::getRadius( ) const {
	return _radius;
}

void Character::setFinished( ) {
	_finished = true;
}

void Character::setActCount( int count ) {
	_act_count = count;
}

void Character::setArea( AREA area ) {
	_area = area;
}
