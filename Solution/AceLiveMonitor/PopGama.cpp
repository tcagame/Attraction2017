#include "PopGama.h"
#include "EnemyGama.h"
#include "Military.h"

const int MAX_POP_COUNT = 1000;

PopGama::PopGama( const Vector& pos ) :
Pop( pos ),
_count( MAX_POP_COUNT ) {
}

PopGama::~PopGama( ) {
}

void PopGama::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > MAX_POP_COUNT ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyGama( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}