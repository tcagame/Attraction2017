#include "PopSwampZombieB.h"
#include "EnemySwampZombieB.h"
#include "Military.h"


PopSwampZombieB::PopSwampZombieB( const Vector& pos ) :
Pop( pos ) {
}


PopSwampZombieB::~PopSwampZombieB( ) {
}

void PopSwampZombieB::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( isInScreen( ) ) {
		EnemyPtr enemy = EnemyPtr( new EnemySwampZombieB( getPos( ) ) );
		Military::getTask( )->popUp( enemy );
		_enemy = enemy;
	}
}
