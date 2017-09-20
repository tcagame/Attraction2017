#include "RockEnemyWaterGhost.h"
#include "RockStorage.h"
#include "RockItemMoney.h"
#include "RockDollHouse.h"

const int HP = 5;
const double ANIM_SPEED = 0.9;

RockEnemyWaterGhost::RockEnemyWaterGhost( const Vector& pos ) :
RockEnemy( pos, DOLL_WATERGHOST, HP, 1, 16, 10, true, true ) {
}


RockEnemyWaterGhost::~RockEnemyWaterGhost( ) {
}

void RockEnemyWaterGhost::act( ) {

}

double RockEnemyWaterGhost::getAnimTime( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	double anim_time = 0;
	double end_time = model->getEndAnimTime( );	
	anim_time = fmod( ( double )getActCount( ) * ANIM_SPEED, end_time );
	return anim_time;
}

void RockEnemyWaterGhost::dropItem( ) {
	RockStorage::getTask( )->addDropItem( RockItemPtr( new RockItemMoney( getPos( ) + Vector( 0, getOverlappedRadius( ), 0 ), RockItemMoney::MONEY_VALUE_3 ) ) );
}