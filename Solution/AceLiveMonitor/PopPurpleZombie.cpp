#include "PopPurpleZombie.h"
#include "EnemyPurpleZombie.h"
#include "Military.h"
#include "Property.h"

PopPurpleZombie::PopPurpleZombie( const Vector& pos ) :
Pop( pos ) {
	_max_pop_time = Property::getTask( )->getData( "PurpleZombie_POP_TIME" );
	_count = _max_pop_time;
}


PopPurpleZombie::~PopPurpleZombie( ) {
}

void PopPurpleZombie::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > _max_pop_time ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyPurpleZombie( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_count = 0;
		}
	}
	_count++;
}