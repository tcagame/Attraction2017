#pragma once
#include "smart_ptr.h"

PTR( RockItem );

class RockPopItem {
public:
	RockPopItem( RockItemPtr item );
	virtual ~RockPopItem( );
public:
	void update( );
	bool isFinished( ) const;
private:
	int _count;
	RockItemPtr _item;
};

