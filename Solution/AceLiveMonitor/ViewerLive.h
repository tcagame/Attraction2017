#pragma once
#include "Task.h"
#include <string>
#include "smart_ptr.h"

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
	ViewerStreetPtr _viewer_street;
	ViewerEventPtr _viewer_event;
	ViewerStatusPtr _viewer_status;
	ViewerProgressBarPtr _viewer_progress;
	ViewerTitlePtr _viewer_title;
	ViewerObjectPtr _viewer_object;
	ViewerDebugPtr _viewer_debug;
	ImagePtr _image_frame;
	ImagePtr _image_cover_entry;
	ImagePtr _image_cover_continue;
	ImagePtr _image_device;
};

