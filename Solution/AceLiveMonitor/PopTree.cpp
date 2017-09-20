#include "PopTree.h"
#include "EnemyTree.h"
#include "Military.h"

const int MAX_POP_COUNT = 2000;

PopTree::PopTree( const Vector& pos ) :
Pop( pos ),
_count( MAX_POP_COUNT ) {
}


PopTree::~PopTree( ) {
}

void PopTree::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > MAX_POP_COUNT ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyTree( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}