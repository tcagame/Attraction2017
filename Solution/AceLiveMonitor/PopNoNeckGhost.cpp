#include "PopNoNeckGhost.h"
#include "EnemyNoNeckGhost.h"
#include "Military.h"
#include "Property.h"

PopNoNeckGhost::PopNoNeckGhost( const Vector& pos ) :
Pop( pos ) {
	_max_pop_time = Property::getTask( )->getData( "NoNeckGhost_POP_TIME" );
	_count = _max_pop_time;
}


PopNoNeckGhost::~PopNoNeckGhost( ) {
}

void PopNoNeckGhost::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > _max_pop_time ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyNoNeckGhost( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}