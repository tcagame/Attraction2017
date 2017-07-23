#pragma once
#include "smart_ptr.h"
#include "Image.h"
#include <array>
#include "ace_define.h"

PTR( Family );

class Viewer {
public:
	Viewer( FamilyConstPtr family );
	virtual ~Viewer( );
public:
	void update( );
private:
	void drawFamily( ) const;
	void drawStreet( ) const;
private:
	FamilyConstPtr _family;
	std::array< ImagePtr, ACE_PLAYER_NUM > _image_family;
	std::array< ImagePtr, ACE_MAP_NUM > _image_back;
	std::array< ImagePtr, ACE_MAP_NUM > _image_front;

};

