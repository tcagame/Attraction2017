#include "PopShishimai.h"
#include "EnemyShishimai.h"
#include "Military.h"
#include "Property.h"

PopShishimai::PopShishimai( const Vector& pos ) :
Pop( pos ) {
	_max_pop_time = Property::getTask( )->getData( "Shishimai_POP_TIME" );
	_count = _max_pop_time;
}


PopShishimai::~PopShishimai( ) {
}


void PopShishimai::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > _max_pop_time ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyShishimai( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}