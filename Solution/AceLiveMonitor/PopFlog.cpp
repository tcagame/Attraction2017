#include "PopFlog.h"
#include "EnemyFlog.h"
#include "Military.h"

const int MAX_POP_COUNT = 300;
const int POP_RANGE = 200;

PopFlog::PopFlog( const Vector& pos ) :
Pop( pos ),
_count( MAX_POP_COUNT ) {
}


PopFlog::~PopFlog( ) {
}

void PopFlog::update( ) {
	//ƒvƒŒƒCƒ„[‚ª‹ß‚­‚É‚«‚½‚ç•¦‚­
	if ( _count > MAX_POP_COUNT ) {
		if ( isInRangePlayer( POP_RANGE ) ) {
			Military::getTask( )->popUp( EnemyPtr( new EnemyFlog( getPos( ) ) ) );
			_count = 0;
		}
	}
	_count++;
}