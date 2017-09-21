#include "PopRedBird.h"
#include "EnemyRedBird.h"
#include "Military.h"
#include "Property.h"

const int POP_RANGE = 400;

PopRedBird::PopRedBird( const Vector& pos ) :
Pop( pos ) {
	_max_pop_time = Property::getTask( )->getData( "RedBird_POP_TIME" );
	_count = _max_pop_time;
}


PopRedBird::~PopRedBird( ) {
}

void PopRedBird::update( ) {
	//ƒvƒŒƒCƒ„[‚ª‹ß‚­‚É‚«‚½‚ç•¦‚­
	if ( _count > _max_pop_time ) {
		if ( isInRangePlayer( POP_RANGE ) ) {
			Military::getTask( )->popUp( EnemyPtr( new EnemyRedBird( getPos( ) ) ) );
			_count = 0;
		}
	}
	_count++;
}