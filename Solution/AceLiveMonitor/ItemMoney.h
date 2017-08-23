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
	ItemMoney( const Vector& pos, TYPE money );
	virtual ~ItemMoney( );
public:
	void setSynchronousData( unsigned char type, int camera_pos ) const;
	int getValue( ) const;
protected:
	void act( );
private:
	TYPE _type;
};

