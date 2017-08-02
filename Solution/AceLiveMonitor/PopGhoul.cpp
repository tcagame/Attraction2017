#include "PopGhoul.h"
#include "EnemyGhoul.h"
#include "Military.h"


PopGhoul::PopGhoul( const Vector& pos ) :
_pos( pos ),
_pop( false ) {
}


PopGhoul::~PopGhoul( ) {
}

void PopGhoul::update( ) {
	if ( !_pop ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemyGhoul( _pos ) ) );
		_pop = true;
	}
}