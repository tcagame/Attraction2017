#include "PopShell.h"
#include "EnemyShell.h"
#include "Military.h"
#include "Property.h"

PopShell::PopShell( const Vector& pos ) :
Pop( pos ) {
	_max_pop_time = Property::getTask( )->getData( "Shell_POP_TIME" );
	_count = _max_pop_time;
}


PopShell::~PopShell( ) {
}

void PopShell::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > _max_pop_time ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyShell( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}