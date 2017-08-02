#include "PopLancer.h"
#include "EnemyLancer.h"
#include "Military.h"

PopLancer::PopLancer( const Vector& pos ) :
_pos( pos ),
_pop( false ) {
}


PopLancer::~PopLancer( ) {
}

void PopLancer::update( ) {
	if ( !_pop ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemyLancer( _pos ) ) );
		_pop = true;
	}
}
