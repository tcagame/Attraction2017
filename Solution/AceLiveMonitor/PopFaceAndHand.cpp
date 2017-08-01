#include "PopFaceAndHand.h"
#include "EnemyFaceAndHand.h"
#include "Military.h"

PopFaceAndHand::PopFaceAndHand( Vector pos ) : 
_pos( pos ),
_pop( false ) {
}

PopFaceAndHand::~PopFaceAndHand( ) {
}

void PopFaceAndHand::update( ) {
	if ( !_pop ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemyFaceAndHand( _pos ) ) );
		_pop = true;
	}	
}