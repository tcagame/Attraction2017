#include "PopLady.h"
#include "EnemyLady.h"
#include "Military.h"
#include "Property.h"

PopLady::PopLady( const Vector& pos ) :
Pop( pos ) {
	_max_pop_time = Property::getTask( )->getData( "Lady_POP_TIME" );
	_count = _max_pop_time;
}

PopLady::~PopLady( ) {
}

void PopLady::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > _max_pop_time ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyLady( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}