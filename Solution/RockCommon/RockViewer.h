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
	void drawBubbles( ) const;
	void drawAncestors( ) const;
	void drawEventCharacter( ) const;
	void drawItem( ) const; 
	void drawAlter( ) const;
	void drawCasket( ) const;
	void drawShadow( ) const;
	void drawUI( ) const;
	void drawResult( ) const;
	void drawDebug( ) const;
	void drawGame( ) const;
private:
	StatusPtr _status;
	ImagePtr _dummy_ui;
	std::vector< ImagePtr > _breasts;
	std::vector< ImagePtr > _image_frame;
	std::vector< ImagePtr > _power;
	std::vector< ImagePtr > _items;
	ImagePtr _virtue;
	ImagePtr _money_num;
	ImagePtr _virtue_num;
};

