#include "PopLancer.h"
#include "EnemyLancer.h"
#include "Military.h"

const int MAX_POP_COUNT = 400;

PopLancer::PopLancer( const Vector& pos ) :
Pop( pos ),
_count( MAX_POP_COUNT ) {
}


PopLancer::~PopLancer( ) {
}


void PopLancer::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > MAX_POP_COUNT ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyLancer( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}