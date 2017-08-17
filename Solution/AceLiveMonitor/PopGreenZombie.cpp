#include "PopGreenZombie.h"
#include "EnemyGreenZombie.h"
#include "Military.h"


PopGreenZombie::PopGreenZombie( const Vector& pos ) :
Pop( pos ) {
}


PopGreenZombie::~PopGreenZombie( ) {
}


void PopGreenZombie::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyGreenZombie( getPos( ) ) ) );
}