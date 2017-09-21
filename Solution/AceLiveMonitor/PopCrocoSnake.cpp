#include "PopCrocoSnake.h"
#include "EnemyCrocoSnake.h"
#include "Military.h"
#include "Property.h"

PopCrocoSnake::PopCrocoSnake( const Vector& pos ) :
Pop( pos ) {
	_max_pop_time = Property::getTask( )->getData( "CrocoSnake_POP_TIME" );
	_count = _max_pop_time;
}


PopCrocoSnake::~PopCrocoSnake( ) {
}

void PopCrocoSnake::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > _max_pop_time ) {
		if ( isInScreen( ) ) {
			Military::getTask( )->popUp( EnemyPtr( new EnemyCrocoSnake( getPos( ) ) ) );
			_count = 0;
		}
	}
	_count++;
}