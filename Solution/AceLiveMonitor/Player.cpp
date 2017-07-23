#include "Player.h"

Player::Player( Vector pos ) :
_pos( pos ) {
}

Player::~Player( ) {
}

void Player::update( ) {
	_pos.y++;
}

Vector Player::getPos( ) const {
	return _pos;
}