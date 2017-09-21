#pragma once
#include "RockItem.h"

PTR( RockItemBubble );

class RockItemTree : public RockItem {
public:
	RockItemTree( const Vector& pos );
	virtual ~RockItemTree( );
public:
	double getAnimTime( ) const;
	void eraseBubble( );
	ModelMV1Ptr getModel( ) const;
private:
	void act( );
private:
	RockItemBubblePtr _bubble;
};

