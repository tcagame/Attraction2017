#include "PopJizo.h"
#include "EnemyJizo.h"
#include "Military.h"

PopJizo::PopJizo( const Vector& pos ) :
_pos( pos ),
_pop( false ) {
}

PopJizo::~PopJizo( ) {
}

void PopJizo::update( ) {
	if ( !_pop ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemyJizo( _pos ) ) );
		_pop = true;
	}
}