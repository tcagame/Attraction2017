#include "PopStoneFace.h"
#include "EnemyStoneFace.h"
#include "Military.h"

const int MAX_POP_COUNT = 300;
const int POP_RANGE = 200;

PopStoneFace::PopStoneFace( const Vector& pos ) :
Pop( pos ),
_count( MAX_POP_COUNT ) {
}

PopStoneFace::~PopStoneFace( ) {
}

void PopStoneFace::update( ) {
	//ƒvƒŒƒCƒ„[‚ª‹ß‚­‚É‚«‚½‚ç•¦‚­
	if ( _count > MAX_POP_COUNT ) {
		if ( isInRangePlayer( POP_RANGE ) ) {
			Military::getTask( )->popUp( EnemyPtr( new EnemyStoneFace( getPos( ) ) ) );
			_count = 0;
		}
	}
	_count++;
}