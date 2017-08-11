#include "PopBat.h"
#include "EnemyBat.h"
#include "Military.h"


PopBat::PopBat( const Vector& pos ) :
_pos( pos ),
_pop( false ) {
}


PopBat::~PopBat( ) {
}

void PopBat::update( ) {
	if ( !_pop ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemyBat( _pos ) ) );
		_pop = true;
	}
}