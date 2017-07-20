#pragma once

class ObjectCursor {
public:
	ObjectCursor( );
	virtual ~ObjectCursor( );
public:
	void update( );
	int getGX( ) const;
	int getGY( ) const;
	bool isOnChip( ) const;
private:
	int _gx;
	int _gy;
};

