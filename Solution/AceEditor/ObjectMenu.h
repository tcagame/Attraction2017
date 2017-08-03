#pragma once
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Image );
PTR( ObjectEditor );

class ObjectMenu {
public:
	ObjectMenu( ImagePtr image_menu, ImagePtr image_block, ImagePtr enemy_midium_image, ImagePtr enemy_big_image, ImagePtr enemy_wide_image, ImagePtr image_event, ObjectEditorPtr object_editor );
	virtual ~ObjectMenu( );
public:
	void update( );
	void draw( ) const;
	void setPos( const Vector& pos );
	bool getActive( ) const;
private:
	enum TAG {
		TAG_BLOCK,
		TAG_ENEMY,
		TAG_EVENT,
		MAX_TAG
	};
	enum GRAPH_ENEMY {
		GRAPH_ENEMY_MIDIUM,
		GRAPH_ENEMY_BIG,
		GRAPH_ENEMY_WIDE,
		MAX_GRAPH_ENEMY,
	};
private:
	unsigned char getObj( int idx ) const;
	unsigned char getEnemy( int idx ) const;
	unsigned char getEvent( int idx ) const;
private:
	int _page;
	bool _active;
	TAG _select_tag;
	Vector _pos;
	ImagePtr _menu;
	ImagePtr _block;
	ImagePtr _enemy[ MAX_GRAPH_ENEMY ];
	ImagePtr _event;
	ObjectEditorPtr _object_editor;
};

