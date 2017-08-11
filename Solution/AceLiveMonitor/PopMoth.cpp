#include "PopMoth.h"
#include "EnemyMoth.h"
#include "Military.h"


PopMoth::PopMoth( const Vector& pos ) :
_pos( pos ),
_pop( false ) {
}


PopMoth::~PopMoth( ) {
}

void PopMoth::update( ) {
	if ( !_pop ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemyMoth( _pos ) ) );
		_pop = true;
	}
}