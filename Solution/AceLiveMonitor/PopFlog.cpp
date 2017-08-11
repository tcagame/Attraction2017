#include "PopFlog.h"
#include "EnemyFlog.h"
#include "Military.h"


PopFlog::PopFlog( const Vector& pos ) :
_pos( pos ),
_pop( false ) {
}


PopFlog::~PopFlog( ) {
}

void PopFlog::update( ) {
	if ( !_pop ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemyFlog( _pos ) ) );
		_pop = true;
	}
}