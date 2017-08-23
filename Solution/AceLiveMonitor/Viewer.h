#pragma once
#include "Task.h"
#include <string>
#include "smart_ptr.h"

PTR( Viewer );
PTR( ViewerStreet );
PTR( ViewerArmoury );
PTR( ViewerEvent );
PTR( ViewerStatus );
PTR( ViewerStorage );
PTR( ViewerMagazine );

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
	ViewerStreetConstPtr _viewer_street;
	ViewerArmouryConstPtr _viewer_armoury;
	ViewerStatusConstPtr _viewer_status;
	ViewerEventConstPtr _viewer_event;
	ViewerStoragePtr _viewer_storage;
	ViewerMagazinePtr _viewer_magazine;

	ViewerDebugConstPtr _viewer_debug;

	ViewerObjectPtr _viewer_object;
};

