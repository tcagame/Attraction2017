#pragma once
#include "RockItem.h"
class RockItemDango : public RockItem {
public:
	RockItemDango( const Vector& pos );
	virtual ~RockItemDango( );
public:
	ModelMV1Ptr getModel( ) const;
};

