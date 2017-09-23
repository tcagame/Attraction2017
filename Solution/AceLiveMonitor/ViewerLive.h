#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include "ace_define.h"
#include <string>
#include <array>

PTR( ViewerLive );
PTR( ViewerStreet );
PTR( ViewerEvent );
PTR( ViewerTitle );
PTR( ViewerStatus );
PTR( ViewerEntry );
PTR( ViewerProgressBar );
PTR( ViewerDebug );
PTR( ViewerObject );
PTR( Image );

class ViewerLive : public Task {
public:
	static std::string getTag( ) { return "VIEWERLIVE"; };
	static ViewerLivePtr getTask( );
public:
	ViewerLive( );
	virtual ~ViewerLive( );
public:
	void initialize( );
	void update( );
private:
	void drawMessage( );
private:
	ViewerStreetPtr _viewer_street;
	ViewerEventPtr _viewer_event;
	ViewerStatusPtr _viewer_status;
	ViewerTitlePtr _viewer_title;
	ViewerObjectPtr _viewer_object;
	ViewerDebugPtr _viewer_debug;
	ImagePtr _image_entry;
	ImagePtr _image_continue;
	ImagePtr _image_frame;
	ImagePtr _image_device;
	ImagePtr _image_fade;
	ImagePtr _image_redo;
	std::array< ImagePtr, MAX_PLAYER > _image_bustup;
	std::array< ImagePtr, MAX_MESSAGE > _image_message;
};

