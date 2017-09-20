#include "PopHugDaemon.h"
#include "EnemyHugDaemon.h"
#include "Military.h"

const int MAX_POP_COUNT = 400;

PopHugDaemon::PopHugDaemon( const Vector& pos ) :
Pop( pos ),
_count( MAX_POP_COUNT ) {
}


PopHugDaemon::~PopHugDaemon( ) {
}

void PopHugDaemon::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > MAX_POP_COUNT ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyHugDaemon( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}