#include "Character.h"
#include "ace_define.h"
#include "Family.h"
#include "Player.h"

const int MAX_SPEED_Y = 10;
const int MAX_ACT_COUNT = 2100000000;

Character::Character( const Vector& pos, int chip_size, bool mass ) :
_pos( pos ),
_vec( Vector( ) ),
_standing( false ),
_chip_size( chip_size ),
_act_count( 0 ),
_mass( mass ) {
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
	if ( _pos.y + _vec.y > VIEW_STREET_Y + VIEW_STREET_HEIGHT ) {
		_standing = true;
		_vec.y = 0;
		_pos.y = VIEW_STREET_Y + VIEW_STREET_HEIGHT - GRAVITY / 2;
	}
	if ( _pos.x + _vec.x - _chip_size / 2 < 0 ) {
		_pos.x = _chip_size / 2;
		_vec.x = 0;
	}
	updateDir( );
	_pos += _vec;
	//—Ž‰ºˆ—

	//•Ç‚É“–‚½‚éˆ—

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
