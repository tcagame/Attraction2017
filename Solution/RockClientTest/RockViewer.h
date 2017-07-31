#pragma once
#include "Task.h"
#include <string>

PTR( RockViewer );

class RockViewer : public Task {
public:
	static std::string getTag( ) { return "ROCKVIEWER"; };
	static RockViewerPtr getTask( );
public:
	RockViewer( );
	virtual ~RockViewer( );
public:
	void update( );
private:
	void drawMap( ) const;
	void drawEnemy( ) const;
};

