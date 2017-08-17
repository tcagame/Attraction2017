#include "PopSwampZombieB.h"
#include "EnemySwampZombieB.h"
#include "Military.h"


PopSwampZombieB::PopSwampZombieB( const Vector& pos ) :
Pop( pos ) {
}


PopSwampZombieB::~PopSwampZombieB( ) {
}

void PopSwampZombieB::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemySwampZombieB( getPos( ) ) ) );
}
