#include "Enemy.h"



Enemy::Enemy( const Vector& pos, const int width, bool mass ) :
Character( pos, width, mass ) {
	setDir( DIR_LEFT );
}


Enemy::~Enemy( ) {
}
