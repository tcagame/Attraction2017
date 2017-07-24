#pragma once
#include "Task.h"
#include <string>
#include "smart_ptr.h"
#include "Image.h"
#include <array>
#include "ace_define.h"

PTR( Family );
PTR( Armoury );
PTR( Viewer );

class Viewer : public Task {
public:
	static std::string getTag( ) { return "VIEWER"; };
	static ViewerPtr getTask( );
public:
	Viewer( );
	virtual ~Viewer( );
public:
	void initialize( );
	void update( );
private:
	void drawFamily( ) const;
	void drawStreet( ) const;
	void drawShot( ) const;
private:
	std::array< ImagePtr, ACE_PLAYER_NUM > _image_family;
	std::array< int, ACE_PLAYER_NUM > _player_count;
	std::array< ImagePtr, ACE_MAP_NUM > _image_back;
	std::array< ImagePtr, ACE_MAP_NUM > _image_front;
	ImagePtr _image_shot;
};

