#include "Character.h"
#include "ace_define.h"
#include "Family.h"
#include "Player.h"
#include "Map.h"

const int MAX_SPEED_Y = 10;
const int MAX_ACT_COUNT = 0xfffffff;

Character::Character( const Vector& pos, int chip_size, bool mass ) :
_pos( pos ),
_vec( Vector( ) ),
_standing( false ),
_chip_size( chip_size ),
_act_count( 0 ),
_mass( mass ),
_radius( chip_size ),
_finished( false ) {
}


Character::~Character( ) {
}

void Character::update( ) {
	act( );

	_act_count++;
	_act_count %= MAX_ACT_COUNT;
	_standing = false;
	if ( _mass ) {
		_vec.y += GRAVITY;
	}
	if ( _vec.y > MAX_SPEED_Y ) {
		_vec.y = MAX_SPEED_Y;
	}
	if ( _vec.y < -MAX_SPEED_Y ) {
		_vec.y = -MAX_SPEED_Y;
	}
	MapConstPtr map( Map::getTask( ) );
	{//ã‰º”»’è
		if ( map->isExistance( _pos + Vector( 0, _vec.y ) ) ) {
			if ( _vec.y > 0 ) {
				_standing = true;
				_vec.y = 0;
				_pos.y = ( int )_pos.y + ( ( int )_pos.y % OBJECT_CHIP_SIZE ) - GRAVITY / 2;
			}
		}
	}
	if ( _pos.x + _vec.x - _chip_size / 2 < 0 ) {
		_pos.x = _chip_size / 2;
		_vec.x = 0;
	}
	updateDir( );
	_pos += _vec;

}

void Character::damage( int force ) {
	_finished = true;
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


bool Character::isStanding( ) const {
	return _standing;
}

bool Character::isFinished( ) const {
	return _finished;
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
	double length = ( _pos - target->getPos( ) ).getLength( );
	double radius = _radius + target->getRadius( );
	return ( length < radius );
}

void Character::setRadius( int radius ) {
	_radius = radius;
}

double Character::getRadius( ) const{
	return _radius;
}

void Character::setFinished( ) {
	_finished = true;
}
