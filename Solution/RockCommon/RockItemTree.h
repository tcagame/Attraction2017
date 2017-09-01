#pragma once
#include "RockItem.h"
class RockItemTree : public RockItem {
public:
	RockItemTree( const Vector& pos );
	virtual ~RockItemTree( );
public:
	ModelMV1Ptr getModel( ) const;
};

