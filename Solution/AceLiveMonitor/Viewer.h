#pragma once
#include "Task.h"
#include <string>
#include "smart_ptr.h"

PTR( Viewer );
PTR( ViewerFamily );
PTR( ViewerStreet );
PTR( ViewerArmoury );

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
	ViewerFamilyConstPtr _viewer_family;
	ViewerStreetConstPtr _viewer_street;
	ViewerArmouryConstPtr _viewer_armoury;
};
