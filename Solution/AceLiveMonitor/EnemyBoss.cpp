#include "EnemyBoss.h"



EnemyBoss::EnemyBoss( const Vector& pos, const int chip_size ) :
Enemy( pos, chip_size, false ) {
	setArea( AREA_EVENT );
}


EnemyBoss::~EnemyBoss( ) {
}
