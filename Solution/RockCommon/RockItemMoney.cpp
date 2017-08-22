#include "RockItemMoney.h"
#include "RockDollHouse.h"



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
	default:
		setDoll( DOLL_MONEY_1 );
		break;
	}
	_value = value;
}

RockItemMoney::~RockItemMoney( ) {
}

ModelMV1Ptr RockItemMoney::getModel( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	model->setTrans( Matrix::makeTransformTranslation( getPos( ) ) );
	return model;
}


int RockItemMoney::getValue( ) const {
	return _value;
}