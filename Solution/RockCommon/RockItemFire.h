#pragma once
#include "RockItem.h"

PTR( RockItemBubble );

class RockItemFire : public RockItem {
public:
	RockItemFire( const Vector& pos );
	virtual ~RockItemFire( );
public:
	void eraseBubble( );
	ModelMV1Ptr getModel( ) const;
	double getAnimTime( ) const;
private:
	void act( );
private:
	RockItemBubblePtr _bubble;
};

