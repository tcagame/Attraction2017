#pragma once
#include "RockItem.h"

class RockItemRock : public RockItem {
public:
	RockItemRock( const Vector& pos );
	virtual ~RockItemRock( );
public:
	ModelMV1Ptr getModel( ) const;
};

