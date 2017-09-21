#include "PopOnyudo.h"
#include "EnemyOnyudo.h"
#include "Military.h"
#include "Property.h"

PopOnyudo::PopOnyudo( const Vector& pos ) :
Pop( pos ) {
	_max_pop_time = Property::getTask( )->getData( "Onyudo_POP_TIME" );
	_count = _max_pop_time;
}

PopOnyudo::~PopOnyudo( ) {
}

void PopOnyudo::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > _max_pop_time ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyOnyudo( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}