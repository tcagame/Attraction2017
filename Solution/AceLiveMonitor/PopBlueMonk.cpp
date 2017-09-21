#include "PopBlueMonk.h"
#include "EnemyBlueMonk.h"
#include "Military.h"
#include "Property.h"

PopBlueMonk::PopBlueMonk( const Vector& pos ) :
Pop( pos ) {
	_max_pop_time = Property::getTask( )->getData( "BlueMonk_POP_TIME" );
	_count = _max_pop_time;
}

PopBlueMonk::~PopBlueMonk( ) {
}


void PopBlueMonk::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > _max_pop_time ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyBlueMonk( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}