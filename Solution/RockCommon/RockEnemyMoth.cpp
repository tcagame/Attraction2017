#include "RockEnemyMoth.h"
#include "RockStorage.h"
#include "RockItemMoney.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockDollHouse.h"

const int HP = 3;
const double ANIM_SPEED = 0.9;

RockEnemyMoth::RockEnemyMoth( const Vector& pos ) :
RockEnemy( pos, DOLL_MOTH, HP, 1, 10, 10, false, true ),
_player_radius( 0 ) {
}

RockEnemyMoth::~RockEnemyMoth( ) {
}

double RockEnemyMoth::getAnimTime( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	double anim_time = 0;
	double end_time = model->getEndAnimTime( );	
	anim_time = fmod( ( double )getActCount( ) * ANIM_SPEED, end_time );
	return anim_time;
}

void RockEnemyMoth::dropItem( ) {
	RockStorage::getTask( )->addDropItem( RockItemPtr( new RockItemMoney( getPos( ) + Vector( 0, getOverlappedRadius( ), 0 ), RockItemMoney::MONEY_VALUE_3 ) ) );
}