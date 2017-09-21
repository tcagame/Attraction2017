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
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > _max_pop_time ) {
		if ( isInRangePlayer( POP_RANGE ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyStoneFace( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}