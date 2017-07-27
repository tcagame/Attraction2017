#pragma once
#include "Task.h"
#include <string>
#include "smart_ptr.h"

PTR( Viewer );
PTR( ViewerFamily );
PTR( ViewerStreet );
PTR( ViewerArmoury );
PTR( ViewerMilitary );
PTR( ViewerEvent );
PTR( ViewerStatus );

PTR( ViewerDebug );

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
	bool _debug;
	ViewerFamilyConstPtr _viewer_family;
	ViewerStreetConstPtr _viewer_street;
	ViewerArmouryConstPtr _viewer_armoury;
	ViewerMilitaryConstPtr _viewer_military;
	ViewerEventConstPtr _viewer_event;
	ViewerStatusConstPtr _viewer_status;

	ViewerDebugConstPtr _viewer_debug;
};

