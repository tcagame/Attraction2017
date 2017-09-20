#include "PopRedBird.h"
#include "EnemyRedBird.h"
#include "Military.h"

const int MAX_POP_COUNT = 400;
const int POP_RANGE = 400;

PopRedBird::PopRedBird( const Vector& pos ) :
Pop( pos ),
_count( MAX_POP_COUNT ) {
}


PopRedBird::~PopRedBird( ) {
}

void PopRedBird::update( ) {
	//ƒvƒŒƒCƒ„[‚ª‹ß‚­‚É‚«‚½‚ç•¦‚­
	if ( _count > MAX_POP_COUNT ) {
		if ( isInRangePlayer( POP_RANGE ) ) {
			Military::getTask( )->popUp( EnemyPtr( new EnemyRedBird( getPos( ) ) ) );
			_count = 0;
		}
	}
	_count++;
}