#pragma once

#include "Task.h"
#include <string>
#include "smart_ptr.h"

PTR( ViewerConsole );
PTR( ViewerObject );

class ViewerConsole : public Task {
public:
	static std::string getTag( ) { return "VIEWERCONSOLE"; };
	static ViewerConsolePtr getTask( );
public:
	ViewerConsole( );
	virtual ~ViewerConsole( );
public:
	void initialize( );
	void update( );
private:
	ViewerObjectPtr _viewer_object;
};

