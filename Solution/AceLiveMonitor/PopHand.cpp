#include "PopHand.h"
#include "EnemyHand.h"
#include "Military.h"

PopHand::PopHand( const Vector& pos ) :
_pos( pos ),
_pop( false ) {
}


PopHand::~PopHand( ) {
}

void PopHand::update( ) {
	if ( !_pop ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemyHand( _pos ) ) );
		_pop = true;
	}
}