#include "PopBlueMonk.h"
#include "EnemyBlueMonk.h"
#include "Military.h"


PopBlueMonk::PopBlueMonk( const Vector& pos ) :
_pos( pos ),
_pop( false ) {
}


PopBlueMonk::~PopBlueMonk( ) {
}

void PopBlueMonk::update( ) {
	if ( !_pop ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemyBlueMonk( _pos ) ) );
		_pop = true;
	}
}