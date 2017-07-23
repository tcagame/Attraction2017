#include "Player.h"
#include "ace_define.h"

const int MAX_SPEED = 10;

Player::Player( Vector pos ) :
_pos( pos ),
_vec( Vector( ) ) {
}

Player::~Player( ) {
}

void Player::update( ) {
	_vec.y += GRAVITY;
	if ( _vec.getLength( ) > MAX_SPEED ) {
		_vec = _vec.normalize( ) * MAX_SPEED;
	}
	if ( _pos.y + _vec.y > SCREEN_HEIGHT ) {
		_pos.y = SCREEN_HEIGHT;
		_vec.y = 0;
	}
	_pos += _vec;
}

Vector Player::getPos( ) const {
	return _pos;
}