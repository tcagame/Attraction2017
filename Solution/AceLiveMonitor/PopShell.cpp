#include "PopShell.h"
#include "EnemyShell.h"
#include "Military.h"

const int MAX_POP_COUNT = 300;

PopShell::PopShell( const Vector& pos ) :
Pop( pos ),
_count( MAX_POP_COUNT ) {
}


PopShell::~PopShell( ) {
}

void PopShell::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > MAX_POP_COUNT ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyShell( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}