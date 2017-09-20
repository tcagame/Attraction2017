#include "PopPurpleZombie.h"
#include "EnemyPurpleZombie.h"
#include "Military.h"

const int MAX_POP_COUNT = 400;

PopPurpleZombie::PopPurpleZombie( const Vector& pos ) :
Pop( pos ),
_count( MAX_POP_COUNT ) {
}


PopPurpleZombie::~PopPurpleZombie( ) {
}

void PopPurpleZombie::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > MAX_POP_COUNT ) {
		if ( isInScreen( ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyPurpleZombie( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_count = 0;
		}
	}
	_count++;
}