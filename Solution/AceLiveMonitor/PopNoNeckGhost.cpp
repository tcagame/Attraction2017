#include "PopNoNeckGhost.h"
#include "EnemyNoNeckGhost.h"
#include "Military.h"

const int MAX_POP_COUNT = 400;

PopNoNeckGhost::PopNoNeckGhost( const Vector& pos ) :
Pop( pos ),
_count( MAX_POP_COUNT ) {
}


PopNoNeckGhost::~PopNoNeckGhost( ) {
}

void PopNoNeckGhost::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > MAX_POP_COUNT ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyNoNeckGhost( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}