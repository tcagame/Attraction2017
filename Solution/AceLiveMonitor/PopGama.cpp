#include "PopGama.h"
#include "EnemyGama.h"
#include "Military.h"
#include "Property.h"

PopGama::PopGama( const Vector& pos ) :
Pop( pos ) {
	_max_pop_time = Property::getTask( )->getData( "Gama_POP_TIME" );
	_count = _max_pop_time;
}

PopGama::~PopGama( ) {
}

void PopGama::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > _max_pop_time ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyGama( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}