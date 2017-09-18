#pragma once
#include "RockItem.h"
#include "ModelMV1.h"

class RockItemToku : public RockItem {
public:
	RockItemToku( const Vector& pos );
	virtual ~RockItemToku( );
public:
	double getAnimTime( ) const;
public:
	ModelMV1Ptr getModel( ) const; 
};

