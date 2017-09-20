#include "PopSkeleton.h"
#include "EnemySkeleton.h"
#include "Military.h"

const int MAX_POP_COUNT = 400;

PopSkeleton::PopSkeleton( const Vector& pos ) :
Pop( pos ),
_count( MAX_POP_COUNT ) {
}

PopSkeleton::~PopSkeleton( ) {
}

void PopSkeleton::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > MAX_POP_COUNT ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemySkeleton( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}