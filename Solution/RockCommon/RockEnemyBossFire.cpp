#include "RockEnemyBossFire.h"
#include "RockStorage.h"
#include "RockItemFire.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockDollHouse.h"
#include "RockMilitary.h"
#include "RockEnemyBossFireAttack.h"

const int HP = 10;
const double ANIM_SPEED = 0.9;
const int SHOT_POS_RANGE = 30;
const int MAX_ATTACK_NUM = 5;
const int ATTACK_TIME = 240;



RockEnemyBossFire::RockEnemyBossFire( const Vector& pos ) :
RockEnemyBoss( pos, DOLL_BOSS_FIRE, HP, 1, 10, 10, true, true ) {
	setDir( Vector( -1, 0, 0 ) );
}


RockEnemyBossFire::~RockEnemyBossFire( ) {
}

void RockEnemyBossFire::act( ) {
	Vector attack_pos = getPos( ) + ( getDir( ) * SHOT_POS_RANGE );
	attack_pos.y += 15;

	const Vector ATTACK_FIRE_POS[ MAX_ATTACK_NUM ] = { 
		Vector( attack_pos.x, attack_pos.y + 30, attack_pos.z ),
		Vector( attack_pos.x, attack_pos.y + 20, attack_pos.z + 20 ),
		Vector( attack_pos.x, attack_pos.y + 10, attack_pos.z + 40 ),
		Vector( attack_pos.x, attack_pos.y + 20, attack_pos.z - 20 ),
		Vector( attack_pos.x, attack_pos.y + 10, attack_pos.z - 40 )
	};

	RockMilitaryPtr military = RockMilitary::getTask( );
	if ( getActCount( ) % ATTACK_TIME == 0 ) {
		for ( int i = 0; i < MAX_ATTACK_NUM; i++ ) {
			military->addEnemy( RockEnemyPtr( new RockEnemyBossFireAttack( ATTACK_FIRE_POS[ i ] ) ) );
		}
	}
}

double RockEnemyBossFire::getAnimTime( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	double anim_time = 0;
	double end_time = model->getEndAnimTime( );	
	anim_time = fmod( ( double )getActCount( ) * ANIM_SPEED, end_time );
	return anim_time;
}

void RockEnemyBossFire::dropItem( ) {
	RockStoragePtr storage( RockStorage::getTask( ) );
	
	storage->addDropItem( RockItemPtr( new RockItemFire( getPos( ) + Vector( 20, getOverlappedRadius( ), 0 ) ) ) );
}

