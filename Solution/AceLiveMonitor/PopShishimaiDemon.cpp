#include "PopShishimaiDemon.h"
#include "EnemyShishimaiDemon.h"
#include "Military.h"

PopShishimaiDemon::PopShishimaiDemon( const Vector& pos ) :
_pos( pos ),
_pop( false ) {
}


PopShishimaiDemon::~PopShishimaiDemon( ) {
}

void PopShishimaiDemon::update( ) {
	if ( !_pop ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemyShishimaiDemon( _pos ) ) );
		_pop = true;
	}
}