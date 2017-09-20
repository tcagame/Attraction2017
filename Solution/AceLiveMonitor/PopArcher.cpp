#include "PopArcher.h"
#include "EnemyArcher.h"
#include "Military.h"

const int MAX_POP_COUNT = 400;

PopArcher::PopArcher( const Vector& pos ) :
Pop( pos ),
_count( MAX_POP_COUNT ) {
}


PopArcher::~PopArcher( ) {
}

void PopArcher::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > MAX_POP_COUNT ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyArcher( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_count = 0;
			_enemy = enemy;
		}
	}
	_count++;
}