#include "PopLady.h"
#include "EnemyLady.h"
#include "Military.h"

const int MAX_POP_COUNT = 400;

PopLady::PopLady( const Vector& pos ) :
Pop( pos ),
_count( MAX_POP_COUNT ) {
}

PopLady::~PopLady( ) {
}

void PopLady::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > MAX_POP_COUNT ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyLady( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}