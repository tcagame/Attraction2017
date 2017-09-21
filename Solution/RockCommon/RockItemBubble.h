#pragma once
#include "RockItem.h"
class RockItemBubble : public RockItem {
public:
	RockItemBubble( const Vector& pos );
	virtual ~RockItemBubble( );
public:
	void setFinished( bool finish );
	bool isFinished( ) const;
	void setPos( const Vector& pos );
	ModelMV1Ptr getModel( ) const;
	double getAnimTime( ) const;
private:
	bool _finished;
};

