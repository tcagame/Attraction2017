#include "PopSkeleton.h"
#include "EnemySkeleton.h"
#include "Military.h"
#include "Property.h"

PopSkeleton::PopSkeleton( const Vector& pos ) :
Pop( pos ) {
	_max_pop_time = Property::getTask( )->getData( "Skeleton_POP_TIME" );
	_count = _max_pop_time;
}

PopSkeleton::~PopSkeleton( ) {
}

void PopSkeleton::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > _max_pop_time ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemySkeleton( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}