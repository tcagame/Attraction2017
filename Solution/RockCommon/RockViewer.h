#pragma once
#include "Task.h"
#include <string>

PTR( RockViewer );
PTR( Status );

class RockViewer : public Task {
public:
	static std::string getTag( ) { return "ROCKVIEWER"; };
	static RockViewerPtr getTask( );
public:
	RockViewer( StatusPtr status );
	virtual ~RockViewer( );
public:
	void update( );
private:
	void drawMap( ) const;
	void drawEnemy( ) const;
	void drawPlayer( ) const;
	void drawShot( ) const;// debug
	void drawItem( ) const; 
private:
	StatusPtr _status;
};

