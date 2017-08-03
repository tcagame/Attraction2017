#include "EnemyBoss.h"



EnemyBoss::EnemyBoss( const Vector& pos, const int chip_size ) :
Enemy( pos, chip_size, false ) {
	setState( Character::STATE_EVENT );
}


EnemyBoss::~EnemyBoss( ) {
}
