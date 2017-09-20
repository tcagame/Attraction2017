#include "PopShishimaiDaemon.h"
#include "EnemyShishimaiDaemon.h"
#include "Military.h"

const int MAX_POP_COUNT = 400;

PopShishimaiDaemon::PopShishimaiDaemon( const Vector& pos ) :
Pop( pos ),
_count( MAX_POP_COUNT ) {
}


PopShishimaiDaemon::~PopShishimaiDaemon( ) {
}

void PopShishimaiDaemon::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > MAX_POP_COUNT ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyShishimaiDaemon( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}