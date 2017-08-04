#include "PopLady.h"
#include "EnemyLady.h"
#include "Military.h"

PopLady::PopLady( const Vector& pos ) :
_pos( pos ),
_pop( false ) {
}

PopLady::~PopLady( ) {
}

void PopLady::update( ) {
	if ( !_pop ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemyLady( _pos ) ) );
		_pop = true;
	}
}