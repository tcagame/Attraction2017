#include "PopWind.h"
#include "EnemyWind.h"
#include "Military.h"

PopWind::PopWind( const Vector& pos ) :
_pos( pos ),
_pop( false ) {
}

PopWind::~PopWind( ) {
}

void PopWind::update( ) {
	if ( !_pop ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemyWind( _pos ) ) );
		_pop = true;
	}
}