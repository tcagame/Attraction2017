#include "RockEnemyFaceAndHand.h"
#include "RockStorage.h"
#include "RockItemMoney.h"

const int HP = 20;

RockEnemyFaceAndHand::RockEnemyFaceAndHand( const Vector& pos ) :
RockEnemy( pos, DOLL_FACE_AND_HAND, HP, 1, 10, 10, true, true ) {
}


RockEnemyFaceAndHand::~RockEnemyFaceAndHand( ) {
}

void RockEnemyFaceAndHand::act( ) {

}

double RockEnemyFaceAndHand::getAnimTime( ) const {
	return 0;
}

void RockEnemyFaceAndHand::dropItem( ) {
	RockStorage::getTask( )->addItem( RockItemPtr( new RockItemMoney( getPos( ) + Vector( 0, getRadius( ), 0 ), RockItemMoney::MONEY_VALUE_3 ) ) );
}