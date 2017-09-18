#include "RockItemMoney.h"
#include "RockDollHouse.h"

static const double ANIM_SPEED = 1.5;


RockItemMoney::RockItemMoney( const Vector& pos, int value ) :
RockItem( pos, DOLL_NONE ) {
	switch( value ) {
	case MONEY_VALUE_1:
		setDoll( DOLL_MONEY_1 );
		break;
	case MONEY_VALUE_2:
		setDoll( DOLL_MONEY_2 );
		break;
	case MONEY_VALUE_3:
		setDoll( DOLL_MONEY_3 );
		break;
	case MONEY_VALUE_4:
		setDoll( DOLL_MONEY_4 );
		break;
	case MONEY_VALUE_5:
		setDoll(DOLL_MONEY_5);
		break;
	case MONEY_VALUE_6:
		setDoll(DOLL_MONEY_6);
		break;
	default:
		setDoll( DOLL_MONEY_1 );
		value = MONEY_VALUE_1;
		break;
	}
	_value = value;
}

RockItemMoney::~RockItemMoney( ) {
}

ModelMV1Ptr RockItemMoney::getModel( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	model->setAnimTime( getAnimTime( ) );
	double rot = Vector( 0, 0, -1 ).angle( getDir( ) );
	Vector axis = Vector( 0, 1, 0 );
	if ( Vector( 0, 0, -1 ).cross( getDir( ) ).y < 0 ) {
		axis = Vector( 0, -1, 0 );
	}
	model->setRot( Matrix::makeTransformRotation( axis, rot ) );
	model->setTrans( Matrix::makeTransformTranslation( getPos( ) ) );
	return model;
}


double RockItemMoney::getAnimTime( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	double anim_time = 0;
	double end_time = model->getEndAnimTime( );	
	anim_time = fmod( ( double )getActCount( ) * ANIM_SPEED, end_time );
	return anim_time;
}

int RockItemMoney::getValue( ) const {
	return _value;
}