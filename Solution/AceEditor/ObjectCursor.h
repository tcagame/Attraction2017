#pragma once
#include "smart_ptr.h"

PTR( Data );

class ObjectCursor {
public:
	ObjectCursor( DataConstPtr data );
	virtual ~ObjectCursor( );
public:
	void update( );
	void setScrollX( int scroll_x );
	int getScrollX( ) const;
	int getGX( ) const;
	int getGY( ) const;
	bool isOnChip( ) const;
private:
	int _gx;
	int _gy;
	int _scroll_x;
	DataConstPtr _data;
};

