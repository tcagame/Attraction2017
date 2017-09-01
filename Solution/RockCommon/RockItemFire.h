#pragma once
#include "RockItem.h"
class RockItemFire : public RockItem {
public:
	RockItemFire( const Vector& pos );
	virtual ~RockItemFire( );
public:
	ModelMV1Ptr getModel( ) const;
};

