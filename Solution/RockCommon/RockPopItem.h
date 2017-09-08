#pragma once
#include "smart_ptr.h"

PTR( RockItem );

class RockPopItem {
public:
	RockPopItem( RockItemPtr item, bool bubble = false );
	virtual ~RockPopItem( );
public:
	void update( );
	bool isFinished( ) const;
private:
	int _count;
	bool _bubble;
	RockItemPtr _item;
};

