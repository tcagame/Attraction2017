#pragma once
#include "RockItem.h"

PTR( RockItemBubble );

class RockItemEnhanceCharge : public RockItem {
public:
	RockItemEnhanceCharge( const Vector& pos );
	virtual ~RockItemEnhanceCharge( );
public:
	double getAnimTime( ) const;
public:
	void eraseBubble( );
	ModelMV1Ptr getModel( ) const;
	RockItemBubblePtr _bubble;
};

