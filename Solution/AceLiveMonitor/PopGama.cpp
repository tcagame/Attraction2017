#include "PopGama.h"
#include "EnemyGama.h"
#include "Military.h"

PopGama::PopGama( const Vector& pos ) :
_pos( pos ),
_pop( false ) {
}

PopGama::~PopGama( ) {
}

void PopGama::update( ) {
	if ( !_pop ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemyGama( _pos ) ) );
		_pop = true;
	}
}