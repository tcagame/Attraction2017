#include "PopSwampZombieC.h"
#include "EnemySwampZombieC.h"
#include "Military.h"

PopSwampZombieC::PopSwampZombieC( const Vector& pos ) :
Pop( pos ) {
}


PopSwampZombieC::~PopSwampZombieC( ) {
}

void PopSwampZombieC::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemySwampZombieC( getPos( ) ) ) );
}
