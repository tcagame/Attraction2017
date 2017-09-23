#pragma once
#include "Item.h"
class ItemDice : public Item {
public:
	ItemDice( const Vector& pos, AREA area );
	virtual ~ItemDice( );
public:
	void setSynchronousData( int camera_pos ) const;
	int getNum( ) const;
	void stop( );
protected:
	void act( );
private:
	int _num;
	bool _stop;
};

