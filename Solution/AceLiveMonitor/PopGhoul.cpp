#include "PopGhoul.h"
#include "EnemyGhoul.h"
#include "Military.h"
#include "Property.h"

PopGhoul::PopGhoul( const Vector& pos ) :
Pop( pos ) {
	_max_pop_time = Property::getTask( )->getData( "Ghoul_POP_TIME" );
	_count = _max_pop_time;
}

PopGhoul::~PopGhoul( ) {
}

void PopGhoul::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > _max_pop_time ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyGhoul( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}