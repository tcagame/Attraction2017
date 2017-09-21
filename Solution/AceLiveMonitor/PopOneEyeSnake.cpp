#include "PopOneEyeSnake.h"
#include "EnemyOneEyeSnake.h"
#include "Military.h"
#include "Property.h"

PopOneEyeSnake::PopOneEyeSnake( const Vector& pos ) :
Pop( pos ) {
	_max_pop_time = Property::getTask( )->getData( "OneEyeSnake_POP_TIME" );
	_count = _max_pop_time;
}


PopOneEyeSnake::~PopOneEyeSnake( ) {
}

void PopOneEyeSnake::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > _max_pop_time ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyOneEyeSnake( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}