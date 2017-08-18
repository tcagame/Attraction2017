#pragma once

class ViewerObject {
public:
	ViewerObject();
	virtual ~ViewerObject( );
public:
	void drawMain( ) const;
	void drawEvent( ) const;
};

