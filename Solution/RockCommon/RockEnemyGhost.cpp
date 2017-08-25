#include "RockEnemyGhost.h"
#include "RockStorage.h"
#include "RockItemMoney.h"

const int HP = 10;

RockEnemyGhost::RockEnemyGhost( const Vector& pos ) :
RockEnemy( pos, DOLL_GHOST, HP, 1, 10, 10, false, false ) {
}


RockEnemyGhost::~RockEnemyGhost( ) {
}

void RockEnemyGhost::act( ) {
	setVec( ( Vector( 0, 40, 0 ) - getPos( ) ).normalize( ) );
}

double RockEnemyGhost::getAnimTime( ) const {
	return 0;
}

void RockEnemyGhost::dropItem( ) {
	RockStorage::getTask( )->addItem( RockItemPtr( new RockItemMoney( getPos( ) + Vector( 0, getRadius( ), 0 ), RockItemMoney::MONEY_VALUE_2 ) ) );
}
