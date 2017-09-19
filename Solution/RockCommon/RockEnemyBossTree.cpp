#include "RockEnemyBossTree.h"
#include "RockStorage.h"
#include "RockitemTree.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockDollHouse.h"
#include "RockMilitary.h"
#include "RockEnemyBossTreeNuts.h"


const int HP = 10;
const double ANIM_SPEED = 0.9;
const int MAX_ATTACK_NUM = 9;
const int ATTACK_TIME = 600;


RockEnemyBossTree::RockEnemyBossTree( const Vector& pos ) :
RockEnemyBoss( pos, DOLL_BOSS_TREE, HP, 1, 10, 10, true, true ) {
	setDir( Vector( -1, 0, 0 ) );
}


RockEnemyBossTree::~RockEnemyBossTree( ) {
}

void RockEnemyBossTree::act( ) {

	Vector attack_pos = getPos( );
	const Vector ATTACK_FIRE_POS[ MAX_ATTACK_NUM ] = { 
		Vector( attack_pos.x + 63, attack_pos.y + 53, attack_pos.z + 4 ),
		Vector( attack_pos.x + 46, attack_pos.y + 68, attack_pos.z + 0 ),
		Vector( attack_pos.x + 28, attack_pos.y + 85, attack_pos.z - 10 ),
		Vector( attack_pos.x + 63, attack_pos.y + 53, attack_pos.z + 4 ),
		Vector( attack_pos.x - 42, attack_pos.y + 49, attack_pos.z - 6 ),
		Vector( attack_pos.x +  6, attack_pos.y + 76, attack_pos.z + 0 ),
		Vector( attack_pos.x - 27, attack_pos.y + 72, attack_pos.z + 0 ),
		Vector( attack_pos.x - 31, attack_pos.y + 91, attack_pos.z - 4 ),
		Vector( attack_pos.x - 45, attack_pos.y + 72, attack_pos.z + 0 ),
	};

		RockMilitaryPtr military = RockMilitary::getTask( );
	if ( getActCount( ) % ATTACK_TIME == 0 ) {
		for ( int i = 0; i < MAX_ATTACK_NUM; i++ ) {
			RockMilitaryPtr military = RockMilitary::getTask( );
			military->addEnemy( RockEnemyPtr( new RockEnemyBossTreeNuts( ATTACK_FIRE_POS[ i ] ) ) );
		}
	}
	

}

double RockEnemyBossTree::getAnimTime( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	double anim_time = 0;
	double end_time = model->getEndAnimTime( );	
	anim_time = fmod( ( double )getActCount( ) * ANIM_SPEED, end_time );
	return anim_time;
}

void RockEnemyBossTree::dropItem( ) {
	RockStoragePtr storage( RockStorage::getTask( ) );
	
	storage->addDropItem( RockItemPtr( new RockItemTree( getPos( ) + Vector( 20, getOverlappedRadius( ), 0 ) ) ) );
}
