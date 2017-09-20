#pragma once
#include "Pop.h"
#include "ItemMoney.h"

class PopMoney : public Pop {
public:
	PopMoney( const Vector& pos, unsigned char type );
	virtual ~PopMoney( );
public:
	void update( );
private:
	unsigned char _type;
	int _count;
	ItemWeakPtr _item;
};

