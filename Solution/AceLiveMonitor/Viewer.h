#pragma once
#include "Task.h"
#include <string>
#include "smart_ptr.h"

PTR( Viewer );
PTR( ViewerStreet );
PTR( ViewerEvent );
PTR( ViewerTitle );
PTR( ViewerStatus );
PTR( ViewerDebug );
PTR( ViewerObject );

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
	ViewerStreetPtr _viewer_street;
	ViewerStatusPtr _viewer_status;
	ViewerEventPtr _viewer_event;
	ViewerTitlePtr _viewer_title;

	ViewerDebugConstPtr _viewer_debug;

	ViewerObjectPtr _viewer_object;
};

