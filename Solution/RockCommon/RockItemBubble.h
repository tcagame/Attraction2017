#pragma once
#include "RockItem.h"
class RockItemBubble : public RockItem {
public:
	RockItemBubble( const Vector& pos );
	virtual ~RockItemBubble( );
public:
	ModelMV1Ptr getModel( ) const;
};

