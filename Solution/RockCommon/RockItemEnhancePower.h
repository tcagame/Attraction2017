#pragma once
#include "RockItem.h"

PTR( RockItemBubble );

class RockItemEnhancePower : public RockItem {
public:
	RockItemEnhancePower( const Vector& pos );
	virtual ~RockItemEnhancePower( );
public:
	void eraseBubble( );
	ModelMV1Ptr getModel( ) const;
	RockItemBubblePtr _bubble;
};

