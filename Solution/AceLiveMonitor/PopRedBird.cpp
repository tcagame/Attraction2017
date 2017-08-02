#include "PopRedBird.h"
#include "EnemyRedBird.h"
#include "Military.h"

PopRedBird::PopRedBird( const Vector& pos ) :
_pos( pos ),
_pop( false ) {
}


PopRedBird::~PopRedBird( ) {
}

void PopRedBird::update( ) {
	if ( !_pop ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemyRedBird( _pos ) ) );
		_pop = true;
	}
}