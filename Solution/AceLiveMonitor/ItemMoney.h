#pragma once
#include "Item.h"

class ItemMoney : public Item {
public:
	ItemMoney( const Vector& pos, unsigned char type, AREA area );
	virtual ~ItemMoney( );
public:
	void setSynchronousData( int camera_pos ) const;
	int getValue( ) const;
protected:
	void act( );
private:
	unsigned char _type;
};

