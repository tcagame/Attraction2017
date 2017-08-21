#pragma once
#include "Image.h"

class ViewerDebug {
public:
	ViewerDebug( );
	virtual ~ViewerDebug( );
public:
	void draw( ) const;
	void drawPlayer( ) const;
	void drawEnemy( ) const;
	void drawShot( ) const;
	void drawChip( ) const;
	void drawConnect( ) const;
	void drawDeviceId( ) const;
private:
	ImagePtr _block;
};

