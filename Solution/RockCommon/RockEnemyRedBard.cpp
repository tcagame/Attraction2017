#include "RockEnemyRedBard.h"
#include "RockStorage.h"
#include "RockItemMoney.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockDollHouse.h"
#include "RockMilitary.h"
#include "RockPop.h"
#include "RockEnemyRedBirdAttack.h"

const int HP = 10;
static const double ANIM_SPEED = 0.9;
const int GENERATE_COUNT = 120;

RockEnemyRedBard::RockEnemyRedBard( const Vector& pos ) :
RockEnemy( pos, DOLL_REDBARD, HP, 1, 10, 10, false, true ) {
}


RockEnemyRedBard::~RockEnemyRedBard( ) {
}

void RockEnemyRedBard::act( ) {
	RockMilitaryPtr military = RockMilitary::getTask( );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		RockPlayerPtr player = RockFamily::getTask( )->getPlayer( i );
		if ( player->isActive( ) || player->isBubble( ) ) {
			if ( getActCount( ) % GENERATE_COUNT == 0 ) {
				military->addEnemy( RockEnemyPtr( new RockEnemyRedBirdAttack( getPos( ) ) ) );
			}
		}
	}
	setVec( Vector( -3, 0, 0 ) );
}

double RockEnemyRedBard::getAnimTime( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	double anim_time = 0;
	double end_time = model->getEndAnimTime( );	
	anim_time = fmod( ( double )getActCount( ) * ANIM_SPEED, end_time );
	return anim_time;
}

void RockEnemyRedBard::dropItem( ) {
	RockStorage::getTask( )->addDropItem( RockItemPtr( new RockItemMoney( getPos( ) + Vector( 0, getOverlappedRadius( ), 0 ), RockItemMoney::MONEY_VALUE_6 ) ) );
}