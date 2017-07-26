#pragma once
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Image );
PTR( ObjectEditor );

class ObjectMenu {
public:
	ObjectMenu( ImagePtr image_menu, ImagePtr image_block, ObjectEditorPtr object_editor );
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
		MAX_TAG
	};
private:
	unsigned char getObj( int idx );
private:
	bool _active;
	TAG _select_tag;
	Vector _pos;
	ImagePtr _menu;
	ImagePtr _block;
	ObjectEditorPtr _object_editor;
};

