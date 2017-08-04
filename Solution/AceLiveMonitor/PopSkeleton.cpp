#include "PopSkeleton.h"
#include "EnemySkeleton.h"
#include "Military.h"

PopSkeleton::PopSkeleton( const Vector& pos ) :
_pos( pos ),
_pop( false ) {
}

PopSkeleton::~PopSkeleton( ) {
}

void PopSkeleton::update( ) {
	if ( !_pop ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemySkeleton( _pos ) ) );
		_pop = true;
	}
}