#include "PopNoNeckGhost.h"
#include "EnemyNoNeckGhost.h"
#include "Military.h"

PopNoNeckGhost::PopNoNeckGhost( const Vector& pos ) :
_pos( pos ),
_pop( false ) {
}


PopNoNeckGhost::~PopNoNeckGhost( ) {
}

void PopNoNeckGhost::update( ) {
	if ( !_pop ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemyNoNeckGhost( _pos ) ) );
		_pop = true;
	}
}