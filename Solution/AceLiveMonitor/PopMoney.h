#pragma once
#include "Pop.h"
#include "ItemMoney.h"

class PopMoney : public Pop {
public:
	PopMoney( const Vector& pos, unsigned char type );
	virtual ~PopMoney( );
protected:
	void create( );
private:
	unsigned char _type;
};

