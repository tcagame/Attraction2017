#include "PopStoneFace.h"
#include "EnemyStoneFace.h"
#include "Military.h"

PopStoneFace::PopStoneFace( const Vector& pos ) :
_pos( pos ),
_pop( false ) {
}

PopStoneFace::~PopStoneFace( ) {
}

void PopStoneFace::update( ) {
	if ( !_pop ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemyStoneFace( _pos ) ) );
		_pop = true;
	}
}