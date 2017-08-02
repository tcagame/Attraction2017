#include "PopSwampZombieC.h"
#include "EnemySwampZombieC.h"
#include "Military.h"

PopSwampZombieC::PopSwampZombieC( const Vector& pos ) :
_pos( pos ),
_pop( false ) {
}


PopSwampZombieC::~PopSwampZombieC( ) {
}

void PopSwampZombieC::update( ) {
	if ( !_pop ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemySwampZombieC( _pos ) ) );
		_pop = true;
	}
}
