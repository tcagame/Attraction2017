#pragma once

#include "Task.h"
#include "smart_ptr.h"
#include "ace_define.h"
#include <array>
#include <string>

PTR( ViewerConsole );
PTR( ViewerObject );
PTR( ViewerStreet );
PTR( ViewerEvent );
PTR( ViewerStatus );
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
	void drawConsole( );
	void drawDevice( );
	void drawAreaEvent( );
	void drawAreaStreet( );
	void drawOpening( );
	void drawMessage( );
	void playSe( );
private:
	int _ending_type;
	const PLAYER _player;
	ViewerObjectPtr _viewer_object;
	ViewerStreetPtr _viewer_street;
	ViewerEventPtr _viewer_event;
	ViewerStatusPtr _viewer_status;
	ImagePtr _image_bar_upper;
	ImagePtr _image_bar_lower;
	ImagePtr _image_minimap;
	ImagePtr _image_device;
	ImagePtr _image_ending;
	ImagePtr _image_entry;
	ImagePtr _image_opening;
	ImagePtr _image_continue;
	std::array< bool, MAX_PLAYER > _dead_se;
	ImagePtr _image_redo;
	std::array< ImagePtr, MAX_PLAYER > _image_bustup;
	std::array< ImagePtr, MAX_MESSAGE > _image_message;
};

