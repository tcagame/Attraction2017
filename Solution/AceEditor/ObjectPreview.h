#pragma once
#include "Image.h"
#include "smart_ptr.h"

PTR( Data );
PTR( ObjectCursor );

class ObjectPreview {
public:
	ObjectPreview( DataConstPtr data, ObjectCursorConstPtr object_cursor, ImagePtr enemy_midium_image, ImagePtr enemy_big_image, ImagePtr enemy_wide_image, ImagePtr enemy_small_image, ImagePtr image_event );
	virtual ~ObjectPreview( );
public:
	void draw( ) const;
private:
	enum GRAPH_ENEMY {
		GRAPH_ENEMY_MIDIUM,
		GRAPH_ENEMY_BIG,
		GRAPH_ENEMY_WIDE,
		GRAPH_ENEMY_SMALL,
		MAX_GRAPH_ENEMY,
	};
private:
	ImagePtr _block;
	ImagePtr _enemy[ MAX_GRAPH_ENEMY ];
	ImagePtr _event;
	ImagePtr _altar; //•§’d
	ImagePtr _choise;
	ImagePtr _money;
	DataConstPtr _data;
	ObjectCursorConstPtr _object_cursor;
};

