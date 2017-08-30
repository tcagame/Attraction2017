#pragma once
#include "RockItem.h"

class RockItemMoney : public RockItem {
public:
	static const int MONEY_VALUE_1 = 100;
	static const int MONEY_VALUE_2 = 500;
	static const int MONEY_VALUE_3 = 1000;
	static const int MONEY_VALUE_4 = 5000;
public:
	RockItemMoney( const Vector& pos, int value );
	virtual ~RockItemMoney( );
public:
	ModelMV1Ptr getModel( ) const;
	int getValue( ) const;
private:
	int _value;
};

