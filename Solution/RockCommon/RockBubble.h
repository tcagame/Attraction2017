#pragma once
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( ModelMV1 );

class RockBubble {
public:
	RockBubble( int id );
	virtual ~RockBubble( );
public:
	void update( );
	bool isActive( ) const;
	ModelMV1Ptr getModel( ) const;
private:
	Vector _pos;
	int _id;
	bool _active;
};

