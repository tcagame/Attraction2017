#include "PopHugDemon.h"
#include "EnemyHugDemon.h"
#include "Military.h"


PopHugDemon::PopHugDemon( const Vector& pos ) :
_pos( pos ),
_pop( false ) {
}


PopHugDemon::~PopHugDemon( ) {
}

void PopHugDemon::update( ) {
	if ( !_pop ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemyHugDemon( _pos ) ) );
		_pop = true;
	}
}