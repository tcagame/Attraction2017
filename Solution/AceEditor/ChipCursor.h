#pragma once
#include "smart_ptr.h"

PTR( Data );

class ChipCursor {
public:
	ChipCursor( DataConstPtr data );
	virtual ~ChipCursor( );
public:
	void update( );
	int getScrollX( ) const;
	int getGX( ) const;
	int getGY( ) const;
	bool isOnChip( ) const;
private:
	int _scroll_x;
	int _gx;
	int _gy;
	DataConstPtr _data;
};

