#include "PopRay.h"
#include "EnemyRay.h"
#include "Military.h"

const int MAX_POP_COUNT = 400;

PopRay::PopRay( const Vector& pos ) :
Pop( pos ),
_count( MAX_POP_COUNT ) {
}

PopRay::~PopRay( ) {
}

void PopRay::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > MAX_POP_COUNT ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyRay( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}