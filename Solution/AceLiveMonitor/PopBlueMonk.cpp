#include "PopBlueMonk.h"
#include "EnemyBlueMonk.h"
#include "Military.h"

const int MAX_POP_COUNT = 400;

PopBlueMonk::PopBlueMonk( const Vector& pos ) :
Pop( pos ),
_count( MAX_POP_COUNT ) {
}


PopBlueMonk::~PopBlueMonk( ) {
}


void PopBlueMonk::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > MAX_POP_COUNT ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyBlueMonk( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}