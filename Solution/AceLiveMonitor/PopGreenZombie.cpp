#include "PopGreenZombie.h"
#include "EnemyGreenZombie.h"
#include "Military.h"
#include "Property.h"

PopGreenZombie::PopGreenZombie( const Vector& pos ) :
Pop( pos ) {
	_max_pop_time = Property::getTask( )->getData( "GreenZombie_POP_TIME" );
	_count = _max_pop_time;
}


PopGreenZombie::~PopGreenZombie( ) {
}

void PopGreenZombie::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > _max_pop_time ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyGreenZombie( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}