#include "RockEnemyBossFireAttack.h"
#include "Effect.h"
#include "RockStudio.h"
#include "RockDollHouse.h"

const int FORCE = 2;
const int READY_TIME = 50;
const Vector VEC( -6, 0 , 0 );

RockEnemyBossFireAttack::RockEnemyBossFireAttack( const Vector pos ) :
RockEnemyAttack( pos, DOLL_NONE, 99, FORCE, 10, 30, false, false ),
_shot( false ) {
	EffectPtr effect = Effect::getTask( );
	_handle = effect->playEffect( RockStudio::getTask( )->getEffectHandle( EFFECT_BOSS_FIRE ) );
}


RockEnemyBossFireAttack::~RockEnemyBossFireAttack( ) {

}

void RockEnemyBossFireAttack::act( ) {
	EffectPtr effect = Effect::getTask( );
	Vector pos = getPos( );
	if ( getActCount( ) > READY_TIME ) {
		pos += VEC;
	}
	setPos( pos );
	effect->updateEffectTransform( _handle, pos + Vector( 0, 15, 0 ), 5 , Vector( 0, 0, -1 ) );
}

ModelMV1Ptr RockEnemyBossFireAttack::getModel( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	model->setTrans( Matrix::makeTransformTranslation( getPos( ) ) );
	return model;
}

double RockEnemyBossFireAttack::getAnimTime( ) const {
	return 0;
}