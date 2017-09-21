#include "PopArcher.h"
#include "EnemyArcher.h"
#include "Military.h"
#include "Property.h"

PopArcher::PopArcher( const Vector& pos ) :
Pop( pos ) {
	_max_pop_time = Property::getTask( )->getData( "Archer_POP_TIME" );
	_count = _max_pop_time;
}


PopArcher::~PopArcher( ) {
}

void PopArcher::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > _max_pop_time ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyArcher( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_count = 0;
			_enemy = enemy;
		}
	}
	_count++;
}
