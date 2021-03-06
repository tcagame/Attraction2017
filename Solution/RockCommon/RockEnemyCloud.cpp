#include "RockEnemyCloud.h"
#include "RockStorage.h"
#include "RockItemMoney.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockDollHouse.h"

const int HP = 5;
const double ACCEL = 0.08;
const double MAX_SPEED = 1;
const double ANIM_SPEED = 0.9;
const Vector SEARCH_RANGE( 1000, 1000, 1000 );

RockEnemyCloud::RockEnemyCloud( const Vector& pos ) :
RockEnemy( pos, DOLL_CLOUD, HP, 1, 10, 10, false, true ),
_player_radius( 0 ) {
}


RockEnemyCloud::~RockEnemyCloud( ) {
}

void RockEnemyCloud::act( ) {
	Vector near_distance = SEARCH_RANGE;
	bool wait = true;
	for (int i = 0; i < ROCK_PLAYER_NUM; i++) {
		RockPlayerPtr player = RockFamily::getTask()->getPlayer(i);
		if (!player->isActive() || player->isBubble()) {
			continue;
		}
		wait = false;
		Vector distance = player->getPos() - getPos();
		if (near_distance.getLength() > distance.getLength()) {
			near_distance = distance;
		}
	}
	if (near_distance != SEARCH_RANGE) {
		Vector dir = near_distance.normalize();
		Vector vec = getVec() + dir * ACCEL;
		if (vec.getLength2() > MAX_SPEED * MAX_SPEED) {
			vec = vec.normalize() * MAX_SPEED;
		}
		setVec(vec);
	}
	if (wait) {
		setVec(Vector());
	}
}

double RockEnemyCloud::getAnimTime( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	double anim_time = 0;
	double end_time = model->getEndAnimTime( );	
	anim_time = fmod( ( double )getActCount( ) * ANIM_SPEED, end_time );
	return anim_time;
}

void RockEnemyCloud::dropItem( ) {
	RockStorage::getTask( )->addDropItem( RockItemPtr( new RockItemMoney( getPos( ) + Vector( 0, getOverlappedRadius( ), 0 ), RockItemMoney::MONEY_VALUE_4 ) ) );
}