#include "PopTurtle.h"
#include "EnemyTurtle.h"
#include "Military.h"

PopTurtle::PopTurtle( const Vector& pos ) :
Pop( pos ) {
}

PopTurtle::~PopTurtle( ) {
}

void PopTurtle::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( isInScreen( ) ) {
		EnemyPtr enemy = EnemyPtr( new EnemyTurtle( getPos( ) ) );
		Military::getTask( )->popUp( enemy );
		_enemy = enemy;
	}
}