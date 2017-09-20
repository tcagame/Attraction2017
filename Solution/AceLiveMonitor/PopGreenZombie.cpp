#include "PopGreenZombie.h"
#include "EnemyGreenZombie.h"
#include "Military.h"

const int MAX_POP_COUNT = 400;

PopGreenZombie::PopGreenZombie( const Vector& pos ) :
Pop( pos ),
_count( MAX_POP_COUNT ) {
}


PopGreenZombie::~PopGreenZombie( ) {
}

void PopGreenZombie::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > MAX_POP_COUNT ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyGreenZombie( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}