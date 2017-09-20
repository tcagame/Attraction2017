#include "PopOnyudo.h"
#include "EnemyOnyudo.h"
#include "Military.h"

const int MAX_POP_COUNT = 1000;

PopOnyudo::PopOnyudo( const Vector& pos ) :
Pop( pos ),
_count( MAX_POP_COUNT ) {
}

PopOnyudo::~PopOnyudo( ) {
}

void PopOnyudo::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > MAX_POP_COUNT ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyOnyudo( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}