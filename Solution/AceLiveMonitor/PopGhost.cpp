#include "PopGhost.h"
#include "EnemyGhost.h"
#include "Military.h"

PopGhost::PopGhost( const Vector& pos ) :
_pos( pos ),
_pop( false ) {
}

PopGhost::~PopGhost( ) {
}

void PopGhost::update( ) {
	if ( !_pop ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemyGhost( _pos ) ) );
		_pop = true;
	}
}
