#include "PopShishimai.h"
#include "EnemyShishimai.h"
#include "Military.h"

const int MAX_POP_COUNT = 400;

PopShishimai::PopShishimai( const Vector& pos ) :
Pop( pos ),
_count( MAX_POP_COUNT ) {
}


PopShishimai::~PopShishimai( ) {
}


void PopShishimai::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > MAX_POP_COUNT ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyShishimai( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}