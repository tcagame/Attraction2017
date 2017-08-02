#include "PopWhiteMist.h"
#include "EnemyWhiteMist.h"
#include "Military.h"

PopWhiteMist::PopWhiteMist( const Vector& pos ) :
_pos( pos ),
_pop( false ) {
}

PopWhiteMist::~PopWhiteMist( ) {
}

void PopWhiteMist::update( ) {
	if ( !_pop ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemyWhiteMist( _pos ) ) );
		_pop = true;
	}
}