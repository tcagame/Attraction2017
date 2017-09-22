#include "PopStone.h"
#include "EnemyStone.h"
#include "Military.h"
#include "Property.h"

PopStone::PopStone( const Vector& pos ) :
Pop( pos ) {
	_max_pop_time = Property::getTask( )->getData( "Stone_POP_TIME" );
	_count = _max_pop_time;
}

PopStone::~PopStone( ) {
}

void PopStone::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > _max_pop_time ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyStone( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}