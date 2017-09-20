#include "PopOneEyeSnake.h"
#include "EnemyOneEyeSnake.h"
#include "Military.h"

const int MAX_POP_COUNT = 400;

PopOneEyeSnake::PopOneEyeSnake( const Vector& pos ) :
Pop( pos ),
_count( MAX_POP_COUNT ) {
}


PopOneEyeSnake::~PopOneEyeSnake( ) {
}

void PopOneEyeSnake::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > MAX_POP_COUNT ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyOneEyeSnake( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}