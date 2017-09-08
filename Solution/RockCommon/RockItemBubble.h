#pragma once
#include "RockItem.h"
class RockItemBubble : public RockItem {
public:
	RockItemBubble( const Vector& pos );
	virtual ~RockItemBubble( );
public:
	void setFinished( bool finish );
	bool isFinished( ) const;
	ModelMV1Ptr getModel( ) const;
private:
	bool _finished;
};

