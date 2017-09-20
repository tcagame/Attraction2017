#include "PopStone.h"
#include "EnemyStone.h"
#include "Military.h"


PopStone::PopStone( const Vector& pos ) :
Pop( pos ) {
}


PopStone::~PopStone( ) {
}

void PopStone::update( ) {
	if ( _enemy.expired( ) ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyStone( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
		}
	}
}