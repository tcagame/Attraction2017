#include "PopSwampZombieA.h"
#include "EnemySwampZombieA.h"
#include "Military.h"


PopSwampZombieA::PopSwampZombieA( const Vector& pos ) :
Pop( pos ) {
}


PopSwampZombieA::~PopSwampZombieA( ) {
}

void PopSwampZombieA::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemySwampZombieA( getPos( ) ) ) );
}
