#include "PopSwampZombieB.h"
#include "EnemySwampZombieB.h"
#include "Military.h"


PopSwampZombieB::PopSwampZombieB( const Vector& pos ) :
_pos( pos ),
_pop( false ) {
}


PopSwampZombieB::~PopSwampZombieB( ) {
}

void PopSwampZombieB::update( ) {
	if ( !_pop ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemySwampZombieB( _pos ) ) );
		_pop = true;
	}
}
