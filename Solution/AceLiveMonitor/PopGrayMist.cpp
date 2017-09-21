#include "PopGrayMist.h"
#include "EnemyGrayMist.h"
#include "Military.h"
#include "Property.h"

const int POP_RANGE = 300;

PopGrayMist::PopGrayMist( const Vector& pos ) :
Pop( pos ) {
	_max_pop_time = Property::getTask( )->getData( "GrayMist_POP_TIME" );
	_count = _max_pop_time;
}

PopGrayMist::~PopGrayMist( ) {
}

void PopGrayMist::update( ) {
	//ƒvƒŒƒCƒ„[‚ª‹ß‚­‚É‚«‚½‚ç•¦‚­
	if ( _count > _max_pop_time ) {
		if ( isInRangePlayer( POP_RANGE ) ) {
			Military::getTask( )->popUp( EnemyPtr( new EnemyGrayMist( getPos( ) ) ) );
			_count = 0;
		}
	}
	_count++;
}