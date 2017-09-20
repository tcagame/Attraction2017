#include "RockEnemyBossRock.h"
#include "RockStorage.h"
#include "RockItemMoney.h"
#include "RockItemRock.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockDollHouse.h"
#include "RockEnemyBossRockAttack.h"
#include "RockMilitary.h"
#include "Effect.h"
#include "RockStudio.h"

static const Vector SOUL_FOOT( 0, 100, 0 );
static const int HP = 20;
static const double ANIM_SPEED = 0.9;
static const Vector STONE_POS[ 9 ] = {
	Vector( 0, 110, 0 ),
	Vector( 0, 86, -28 ),
	Vector( 19, 87, -26 ),
	Vector( 23, 91, -11 ),
	Vector( 23, 93, 15 ),
	Vector( -24, 99, 4 ),
	Vector( 2, 98, 22 ),
	Vector( -11, 91, 18 ),
	Vector( -22, 92, -17 )
};
static const Vector STONE_DIR[ 9 ] = {
	Vector( 0, 0, 0 ),
	Vector( 0, 0, -1 ),
	Vector( 1, 0, -1 ),
	Vector( 1, 0, 0 ),
	Vector( 1, 0, 1 ),
	Vector( 0, 0, 1 ),
	Vector( -1, 0, 1 ),
	Vector( -1, 0, 0 ),
	Vector( -1, 0, -1 ),
};

RockEnemyBossRock::RockEnemyBossRock( const Vector& pos ) :
RockEnemyBoss( pos, DOLL_BOSS_ROCK, HP, 1, 30, 10, true, false ),
_soul_handle( -1 ) {
	setDir( Vector( -1, 0, 0 ) );
	RockMilitaryPtr military = RockMilitary::getTask( );
	for ( int i = 0; i < STONE_NUM; i++ ) {
		Vector pos = getPos( ) + STONE_POS[ i ];
		_stones[ i ] = RockEnemyBossRockAttackPtr( new RockEnemyBossRockAttack( pos, (DOLL)( i + DOLL_BOSS_ROCK_ATTACK_1 ), STONE_DIR[ i ] ) );
		military->addEnemy( _stones[ i ] );
	}
}


RockEnemyBossRock::~RockEnemyBossRock( ) {
}

void RockEnemyBossRock::act( ) {
	EffectPtr effect = Effect::getTask( );
	if ( _soul_handle < 0 ) {
		RockStudioPtr studio = RockStudio::getTask( );
		_soul_handle = effect->playEffect( studio->getEffectHandle( EFFECT_ROCK_SOUL ) );
	}
	effect->updateEffectTransform( _soul_handle, getPos( ) + SOUL_FOOT );
}

double RockEnemyBossRock::getAnimTime( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	double anim_time = 0;
	double end_time = model->getEndAnimTime( );	
	anim_time = fmod( ( double )getActCount( ) * ANIM_SPEED, end_time );
	return anim_time;
}

void RockEnemyBossRock::dropItem( ) {
	RockStoragePtr storage( RockStorage::getTask( ) );
	
	storage->addDropItem( RockItemPtr( new RockItemRock( getPos( ) + Vector( 20, getOverlappedRadius( ), 0 ) ) ) );
}

void RockEnemyBossRock::stopEffect( ) {
	Effect::getTask( )->stopEffect( _soul_handle );
}
