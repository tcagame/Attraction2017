#pragma once
#include "smart_ptr.h"
#include "Image.h"
#include <array>
#include "ace_define.h"

PTR( Family );
PTR( PsychicManager );

class Viewer {
public:
	Viewer( FamilyConstPtr family, PsychicManagerConstPtr psychic_manager );
	virtual ~Viewer( );
public:
	void update( );
private:
	void drawFamily( ) const;
	void drawStreet( ) const;
	void drawPsychic( ) const;
private:
	FamilyConstPtr _family;
	PsychicManagerConstPtr _psychic_manager;
	std::array< ImagePtr, ACE_PLAYER_NUM > _image_family;
	std::array< int, ACE_PLAYER_NUM > _player_count;
	std::array< ImagePtr, ACE_MAP_NUM > _image_back;
	std::array< ImagePtr, ACE_MAP_NUM > _image_front;
	ImagePtr _image_psychic;
};

