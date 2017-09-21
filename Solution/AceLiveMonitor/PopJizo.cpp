#include "PopJizo.h"
#include "EnemyJizo.h"
#include "Military.h"
#include "Property.h"

const int POP_RANGE = 400;

PopJizo::PopJizo( const Vector& pos ) :
Pop( pos ) {
	_max_pop_time = Property::getTask( )->getData( "Jizo_POP_TIME" );
	_count = _max_pop_time;
}

PopJizo::~PopJizo( ) {
}

void PopJizo::update( ) {
	//ƒvƒŒƒCƒ„[‚ª‹ß‚­‚É‚«‚½‚ç•¦‚­
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > _max_pop_time ) {
		if ( isInRangePlayer( POP_RANGE ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyJizo( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}