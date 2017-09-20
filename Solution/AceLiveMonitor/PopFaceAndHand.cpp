#include "PopFaceAndHand.h"
#include "EnemyFaceAndHand.h"
#include "Military.h"

const int MAX_POP_COUNT = 300;
const int POP_RANGE = 300;

PopFaceAndHand::PopFaceAndHand( const Vector& pos ) : 
Pop( pos ),
_count( MAX_POP_COUNT ) {
}

PopFaceAndHand::~PopFaceAndHand( ) {
}

void PopFaceAndHand::update( ) {
	//ƒvƒŒƒCƒ„[‚ª‹ß‚­‚É‚«‚½‚ç•¦‚­
	if ( _count > MAX_POP_COUNT ) {
		if ( isInRangePlayer( POP_RANGE ) ) {
			Military::getTask( )->popUp( EnemyPtr( new EnemyFaceAndHand( getPos( ) ) ) );
			_count = 0;
		}
	}
	_count++;
}