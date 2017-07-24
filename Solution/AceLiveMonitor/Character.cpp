#include "Character.h"
#include "ace_define.h"

const int MAX_SPEED_Y = 10;

Character::Character( const Vector& pos, int chip_size ) :
_pos( pos ),
_vec( Vector( ) ),
_standing( false ),
_chip_size( chip_size ) {
}


Character::~Character( ) {
}

void Character::update( ) {
	act( );

	_standing = false;
	_vec.y += GRAVITY;
	if ( _vec.y > MAX_SPEED_Y ) {
		_vec.y = MAX_SPEED_Y;
	}
	if ( _vec.y < -MAX_SPEED_Y ) {
		_vec.y = -MAX_SPEED_Y;
	}
	if ( _pos.y + _vec.y > SCREEN_HEIGHT ) {
		_standing = true;
		_vec.y = 0;
		_pos.y = SCREEN_HEIGHT - GRAVITY / 2;
	}
	if ( _pos.x + _vec.x - _chip_size / 2 < 0 ) {
		_pos.x = _chip_size / 2;
		_vec.x = 0;
	}
	if ( _pos.x + _vec.x + _chip_size / 2 > SCREEN_WIDTH ) {
		_pos.x = SCREEN_WIDTH - _chip_size / 2;
		_vec.x = 0;
	}
	updateDir( );
	_pos += _vec;
	//óéâ∫èàóù

	//ï«Ç…ìñÇΩÇÈèàóù

}

Character::DIR Character::getDir( ) const {
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

