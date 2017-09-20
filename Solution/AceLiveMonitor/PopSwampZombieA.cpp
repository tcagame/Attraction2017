#include "PopSwampZombieA.h"
#include "EnemySwampZombieA.h"
#include "Military.h"


PopSwampZombieA::PopSwampZombieA( const Vector& pos ) :
Pop( pos ) {
}


PopSwampZombieA::~PopSwampZombieA( ) {
}

void PopSwampZombieA::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( isInScreen( ) ) {
		EnemyPtr enemy = EnemyPtr( new EnemySwampZombieA( getPos( ) ) );
		Military::getTask( )->popUp( enemy );
		_enemy = enemy;
	}
}
