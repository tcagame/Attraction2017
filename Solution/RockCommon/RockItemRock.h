#pragma once
#include "RockItem.h"

PTR( RockItemBubble );

class RockItemRock : public RockItem {
public:
	RockItemRock( const Vector& pos );
	virtual ~RockItemRock( );
public:
	double getAnimTime( ) const;
	void eraseBubble( );
	ModelMV1Ptr getModel( ) const;
private:
	void act( );
private:
	RockItemBubblePtr _bubble;
};

