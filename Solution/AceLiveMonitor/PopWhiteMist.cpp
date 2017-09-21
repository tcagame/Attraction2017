#include "PopWhiteMist.h"
#include "EnemyWhiteMist.h"
#include "Military.h"
#include "Property.h"

const int POP_RANGE = 300;

PopWhiteMist::PopWhiteMist( const Vector& pos ) :
Pop( pos ) {
	_max_pop_time = Property::getTask( )->getData( "WhiteMist_POP_TIME" );
	_count = _max_pop_time;
}

PopWhiteMist::~PopWhiteMist( ) {
}

void PopWhiteMist::update( ) {
	//ƒvƒŒƒCƒ„[‚ª‹ß‚­‚É‚«‚½‚ç•¦‚­
	if ( _count > _max_pop_time ) {
		if ( isInRangePlayer( POP_RANGE ) ) {
			Military::getTask( )->popUp( EnemyPtr( new EnemyWhiteMist( getPos( ) ) ) );
			_count = 0;
		}
	}
	_count++;
}