#include "PopLancer.h"
#include "EnemyLancer.h"
#include "Military.h"
#include "Property.h"

PopLancer::PopLancer( const Vector& pos ) :
Pop( pos ) {
	_max_pop_time = Property::getTask( )->getData( "Lancer_POP_TIME" );
	_count = _max_pop_time;
}


PopLancer::~PopLancer( ) {
}


void PopLancer::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > _max_pop_time ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyLancer( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}