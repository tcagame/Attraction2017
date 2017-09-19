#pragma once
#include "Item.h"

class ItemMoney : public Item {
public:
	enum TYPE {
		TYPE_PETTY,
		TYPE_BAG,
		TYPE_500,
	};
public:
	ItemMoney( const Vector& pos, TYPE money, AREA area );
	virtual ~ItemMoney( );
public:
	void setSynchronousData( int camera_pos ) const;
	int getValue( ) const;
protected:
	void act( );
private:
	TYPE _type;
};

