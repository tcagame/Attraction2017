#include "EnemyBoss.h"



EnemyBoss::EnemyBoss( const Vector& pos, const int chip_size, const int hp ) :
Enemy( pos, chip_size, hp, false ) {
	setState( Character::STATE_EVENT );
}


EnemyBoss::~EnemyBoss( ) {
}
