#include "PopStone.h"
#include "EnemyStone.h"
#include "Military.h"


PopStone::PopStone( const Vector& pos ) :
_pos( pos ),
_pop( false ) {
}


PopStone::~PopStone( ) {
}

void PopStone::update( ) {
	if ( !_pop ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemyStone( _pos ) ) );
		_pop = true;
	}
}