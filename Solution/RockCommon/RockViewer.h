#pragma once
#include "Task.h"
#include <string>
#include "Image.h"
#include <vector>

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
	void drawCleannessMap( ) const;
	void drawEnemy( ) const;
	void drawPlayer( ) const;
	void drawBubble( ) const;
	void drawAncestors( ) const;
	void drawEventCharacter( ) const;
	void drawShot( ) const;// debug
	void drawItem( ) const; 
	void drawAlter( ) const;
	void drawCasket( ) const;
	void drawShadow( ) const;
	void drawUI( ) const;
	void drawMovie( ) const;
private:
	StatusPtr _status;
	ImagePtr _image_frame;
	ImagePtr _status_ui;
	ImagePtr _status_num;
	ImagePtr _dummy_ui;
	std::vector< ImagePtr > _breasts;
};

