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
	Chip getChip( ) const;
protected:
	void act( );
private:
	TYPE _type;
};

