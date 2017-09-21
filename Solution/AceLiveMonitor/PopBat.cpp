#include "PopBat.h"
#include "EnemyBat.h"
#include "Military.h"
#include "Property.h"

const int POP_RANGE = 250;

PopBat::PopBat( const Vector& pos ) :
Pop( pos ) {
	_max_pop_time = Property::getTask( )->getData( "Bat_POP_TIME" );
	_count = _max_pop_time;
}


PopBat::~PopBat( ) {
}

void PopBat::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	//ƒvƒŒƒCƒ„[‚ª‹ß‚­‚É‚«‚½‚ç•¦‚­
	if ( _count > _max_pop_time ) {
		if ( isInRangePlayer( POP_RANGE ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyBat( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_count = 0;
			_enemy = enemy;
		}
	}
	_count++;
}