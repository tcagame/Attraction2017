#include "PopCrocoSnake.h"
#include "EnemyCrocoSnake.h"
#include "Military.h"

const int MAX_POP_COUNT = 400;

PopCrocoSnake::PopCrocoSnake( const Vector& pos ) :
Pop( pos ),
_count( MAX_POP_COUNT ) {
}


PopCrocoSnake::~PopCrocoSnake( ) {
}

void PopCrocoSnake::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > MAX_POP_COUNT ) {
		if ( isInScreen( ) ) {
			Military::getTask( )->popUp( EnemyPtr( new EnemyCrocoSnake( getPos( ) ) ) );
			_count = 0;
		}
	}
	_count++;
}