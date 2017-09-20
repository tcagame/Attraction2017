#include "PopGhoul.h"
#include "EnemyGhoul.h"
#include "Military.h"

const int MAX_POP_COUNT = 400;

PopGhoul::PopGhoul( const Vector& pos ) :
Pop( pos ),
_count( MAX_POP_COUNT ) {
}

PopGhoul::~PopGhoul( ) {
}

void PopGhoul::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > MAX_POP_COUNT ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyGhoul( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}