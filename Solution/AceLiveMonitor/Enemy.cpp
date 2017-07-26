#include "Enemy.h"



Enemy::Enemy( const Vector& pos, const int width ) :
Character( pos, width ) {
	setDir( DIR::DIR_LEFT );
}


Enemy::~Enemy( ) {
}
