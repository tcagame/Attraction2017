#pragma once
#include "Item.h"

class ItemVirtue : public Item {
public:
	ItemVirtue( Vector pos );
	virtual ~ItemVirtue( );
public:
	void setSynchronousData( int camera_pos ) const;
protected:
	void act( );
private:
	Vector _target;
};

