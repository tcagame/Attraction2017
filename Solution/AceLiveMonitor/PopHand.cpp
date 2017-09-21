#include "PopHand.h"
#include "EnemyHand.h"
#include "Military.h"
#include "Property.h"

const int POP_RANGE = 350;

PopHand::PopHand( const Vector& pos ) :
Pop( pos ) {
	_max_pop_time = Property::getTask( )->getData( "Hand_POP_TIME" );
	_count = _max_pop_time;
}


PopHand::~PopHand( ) {
}

void PopHand::update( ) {
	//ƒvƒŒƒCƒ„[‚ª‹ß‚­‚É‚«‚½‚ç•¦‚­
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > _max_pop_time ) {
		if ( isInRangePlayer( POP_RANGE ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyHand( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}