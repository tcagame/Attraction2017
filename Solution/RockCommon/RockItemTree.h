#pragma once
#include "RockItem.h"

PTR( RockItemBubble );

class RockItemTree : public RockItem {
public:
	RockItemTree( const Vector& pos );
	virtual ~RockItemTree( );
public:
	double getAnimTime( ) const;
public:
	void eraseBubble( );
	ModelMV1Ptr getModel( ) const;
	RockItemBubblePtr _bubble;
};

