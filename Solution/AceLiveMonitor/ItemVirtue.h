#pragma once

#include "Item.h"
#include "smart_ptr.h"

PTR( ItemVirtue );

class ItemVirtue : public Item {
public:
	ItemVirtue( int target_x );
	virtual ~ItemVirtue( );
public:
	void setSynchronousData( int camera_pos ) const;
protected:
	void act( );
private:
	Vector _target;
};

