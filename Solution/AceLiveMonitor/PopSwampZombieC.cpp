#include "PopSwampZombieC.h"
#include "EnemySwampZombieC.h"
#include "Military.h"

PopSwampZombieC::PopSwampZombieC( const Vector& pos ) :
Pop( pos ) {
}


PopSwampZombieC::~PopSwampZombieC( ) {
}

void PopSwampZombieC::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( isInScreen( ) ) {
		EnemyPtr enemy = EnemyPtr( new EnemySwampZombieC( getPos( ) ) );
		Military::getTask( )->popUp( enemy );
		_enemy = enemy;
	}
}