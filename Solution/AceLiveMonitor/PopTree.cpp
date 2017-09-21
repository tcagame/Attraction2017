#include "PopTree.h"
#include "EnemyTree.h"
#include "Military.h"
#include "Property.h"

PopTree::PopTree( const Vector& pos ) :
Pop( pos ) {
	_max_pop_time = Property::getTask( )->getData( "Tree_POP_TIME" );
	_count = _max_pop_time;
}


PopTree::~PopTree( ) {
}

void PopTree::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > _max_pop_time ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyTree( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}