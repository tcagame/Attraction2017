#include "PopOnyudo.h"
#include "EnemyOnyudo.h"
#include "Military.h"

PopOnyudo::PopOnyudo( const Vector& pos ) :
_pos( pos ),
_pop( false ) {
}

PopOnyudo::~PopOnyudo( ) {
}

void PopOnyudo::update( ) {
	if ( !_pop ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemyOnyudo( _pos ) ) );
		_pop = true;
	}
}