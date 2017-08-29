#pragma once
#include "Task.h"
#include <string>
#include "Image.h"

PTR( RockViewer );
PTR( Status );
PTR( Movie );

class RockViewer : public Task {
public:
	static std::string getTag( ) { return "ROCKVIEWER"; };
	static RockViewerPtr getTask( );
public:
	RockViewer( StatusPtr status );
	virtual ~RockViewer( );
public:
	void update( );
	void initialize( );
private:
	void drawMap( ) const;
	void drawEnemy( ) const;
	void drawPlayer( ) const;
	void drawBubble( ) const;
	void drawAncestors( ) const;
	void drawShot( ) const;// debug
	void drawItem( ) const; 
	void drawAlter( ) const;
	void drawCasket( ) const;
	void drawUI( ) const;
	void drawMovie( ) const;
private:
	StatusPtr _status;
	ImagePtr _status_flame;
	ImagePtr _status_ui;
	ImagePtr _status_num;
};

