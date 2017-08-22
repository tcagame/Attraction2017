#pragma once

#include "Task.h"
#include "smart_ptr.h"
#include "ace_define.h"
#include <string>

PTR( ViewerConsole );
PTR( ViewerObject );
PTR( Image );

class ViewerConsole : public Task {
public:
	static std::string getTag( ) { return "VIEWERCONSOLE"; };
	static ViewerConsolePtr getTask( );
public:
	ViewerConsole( PLAYER player );
	virtual ~ViewerConsole( );
public:
	void initialize( );
	void update( );
private:
	void drawArea( );
	void drawUI( );
private:
	const PLAYER _player;
	ViewerObjectPtr _viewer_object;
	ImagePtr _image_bar_upper;
	ImagePtr _image_bar_lower;
	ImagePtr _image_status;
	ImagePtr _image_minimap;
};

