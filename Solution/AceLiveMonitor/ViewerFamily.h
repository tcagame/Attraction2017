#pragma once
#include "smart_ptr.h"
#include <array>
#include "Image.h"
#include "ace_define.h"

PTR( Family );

class ViewerFamily {
public:
	ViewerFamily( FamilyConstPtr family );
	virtual ~ViewerFamily( );
public:
	void draw( ) const;
private:
	FamilyConstPtr _family;
	std::array< ImagePtr, ACE_PLAYER_NUM > _image_family;
};

