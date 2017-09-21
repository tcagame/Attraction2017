#include "PopRay.h"
#include "EnemyRay.h"
#include "Military.h"
#include "Property.h"

PopRay::PopRay( const Vector& pos ) :
Pop( pos ) {
	_max_pop_time = Property::getTask( )->getData( "Ray_POP_TIME" );
	_count = _max_pop_time;
}

PopRay::~PopRay( ) {
}

void PopRay::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > _max_pop_time ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyRay( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}