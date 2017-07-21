#include "ObjectEditor.h"
#include "Mouse.h"
#include "ObjectCursor.h"
#include "Data.h"
#include "ace_define.h"

ObjectEditor::ObjectEditor( DataPtr data, ObjectCursorConstPtr object_cursor ) :
_data( data ),
_object_cursor( object_cursor ) {
}

ObjectEditor::~ObjectEditor( ) {
}

void ObjectEditor::update( ) {
	MousePtr mouse( Mouse::getTask( ) );
	if ( mouse->isHoldLeftButton( ) && _object_cursor->isOnChip( ) ) {
		int ox = _object_cursor->getGX( ) + _object_cursor->getScrollX( );
		int oy = _object_cursor->getGY( );
		_data->setBlockData( ox, oy, OBJECT_BLOCK );
	}
}