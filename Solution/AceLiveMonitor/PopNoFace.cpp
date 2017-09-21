#include "PopNoFace.h"
#include "EnemyNoFace.h"
#include "Military.h"
#include "Property.h"

const int POP_RANGE = 400;

PopNoFace::PopNoFace( const Vector& pos ) :
Pop( pos ) {
	_max_pop_time = Property::getTask( )->getData( "NoFace_POP_TIME" );
	_count = _max_pop_time;
}

PopNoFace::~PopNoFace( ) {
}

void PopNoFace::update( ) {
	//ƒvƒŒƒCƒ„[‚ª‹ß‚­‚É‚«‚½‚ç•¦‚­
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > _max_pop_time ) {
		if ( isInRangePlayer( POP_RANGE ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyNoFace( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}