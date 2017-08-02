#include "PopSwampZombieA.h"
#include "EnemySwampZombieA.h"
#include "Military.h"


PopSwampZombieA::PopSwampZombieA( const Vector& pos ) :
_pos( pos ),
_pop( false ) {
}


PopSwampZombieA::~PopSwampZombieA( ) {
}

void PopSwampZombieA::update( ) {
	if ( !_pop ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemySwampZombieA( _pos ) ) );
		_pop = true;
	}
}
