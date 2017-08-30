#pragma once
#include "Task.h"
#include <string>
#include "smart_ptr.h"

PTR( ViewerLive );
PTR( ViewerStreet );
PTR( ViewerEvent );
PTR( ViewerTitle );
PTR( ViewerStatus );
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
	ViewerStatusPtr _viewer_status;
	ViewerEventPtr _viewer_event;
	ViewerTitlePtr _viewer_title;
	ViewerObjectPtr _viewer_object;
	ViewerDebugConstPtr _viewer_debug;
	ImagePtr _image_frame;
};

