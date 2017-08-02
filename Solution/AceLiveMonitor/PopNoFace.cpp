#include "PopNoFace.h"
#include "EnemyNoFace.h"
#include "Military.h"

PopNoFace::PopNoFace( Vector pos ) :
_pos( pos ),
_pop( false ) {
}

PopNoFace::~PopNoFace( ) {
}

void PopNoFace::update( ) {
	if ( !_pop ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemyNoFace( _pos ) ) );
		_pop = true;
	}
}