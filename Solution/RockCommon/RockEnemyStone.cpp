#include "RockEnemyStone.h"
#include "RockStorage.h"
#include "RockItemMoney.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockDollHouse.h"

const int HP = 999;
const double ACCEL = 0.1;
const double MAX_SPEED = 1.5;
const double ANIM_SPEED = 0.9;

RockEnemyStone::RockEnemyStone( const Vector& pos ) :
RockEnemy( pos, DOLL_STONE, HP, 1, 10, 10, true, true ),
_player_radius( 0 ),
_rot( 0 ) {
	setVec( Vector( -1, 0, 0 ) );
}


RockEnemyStone::~RockEnemyStone( ) {
}

void RockEnemyStone::act( ) {
	if ( getActCount( ) % 30 == 0 ) {
		setVec( Vector( getVec( ).x, 3, getVec( ).z ) );
	}
}

ModelMV1Ptr RockEnemyStone::getModel( ) {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	model->setAnimTime( getAnimTime( ) );
	
	//c‚É‰ñ“]
	_rot += getVec( ).getLength( ) * 0.2;
	Vector axis = Matrix::makeTransformRotation( Vector( 0, -1, 0 ), PI / 2 ).multiply( getDir( ) );
	Matrix rot = Matrix::makeTransformRotation( axis, _rot );
	model->setRot( rot );

	//À•W
	model->setTrans( Matrix::makeTransformTranslation( getPos( ) + Vector( 0, getOverlappedRadius( ), 0 ) ) );
	return model;
}

double RockEnemyStone::getAnimTime( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	double anim_time = 0;
	double end_time = model->getEndAnimTime( );	
	anim_time = fmod( ( double )getActCount( ) * ANIM_SPEED, end_time );
	return anim_time;
}

void RockEnemyStone::dropItem( ) {
	RockStorage::getTask( )->addDropItem( RockItemPtr( new RockItemMoney( getPos( ) + Vector( 0, getOverlappedRadius( ), 0 ), RockItemMoney::MONEY_VALUE_3 ) ) );
}