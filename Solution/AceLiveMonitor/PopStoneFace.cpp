#include "PopStoneFace.h"
#include "EnemyStoneFace.h"
#include "Military.h"
#include "Property.h"

const int POP_RANGE = 300;

PopStoneFace::PopStoneFace( const Vector& pos ) :
Pop( pos ) {
	_max_pop_time = Property::getTask( )->getData( "StoneFace_POP_TIME" );
	_count = _max_pop_time;
}

PopStoneFace::~PopStoneFace( ) {
}

void PopStoneFace::update( ) {
	//ƒvƒŒƒCƒ„[‚ª‹ß‚­‚É‚«‚½‚ç•¦‚­
	if ( _count > _max_pop_time ) {
		if ( isInRangePlayer( POP_RANGE ) ) {
			Military::getTask( )->popUp( EnemyPtr( new EnemyStoneFace( getPos( ) ) ) );
			_count = 0;
		}
	}
	_count++;
}