#pragma once
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Image );

class ObjectMenu {
public:
	ObjectMenu( ImagePtr image_menu );
	virtual ~ObjectMenu( );
public:
	void update( );
	void draw( ) const;
	void setPos( const Vector& pos );
	bool getActive( ) const;
private:
	bool _active;
	Vector _pos;
	ImagePtr _image;
};

