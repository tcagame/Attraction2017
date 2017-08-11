#include "PopEyeDemon.h"
#include "EnemyEyeDemon.h"
#include "Military.h"


PopEyeDemon::PopEyeDemon( const Vector& pos ) :
_pos( pos ),
_pop( false ) {
}


PopEyeDemon::~PopEyeDemon( ) {
}

void PopEyeDemon::update( ) {
	if ( !_pop ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemyEyeDemon( _pos ) ) );
		_pop = true;
	}
}