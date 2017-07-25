#include "ObjectEditor.h"
#include "Mouse.h"
#include "ObjectCursor.h"
#include "Data.h"
#include "ace_define.h"
#include "Application.h"

const std::string DIRECTORY = "../Resource/Ace/MapData/";

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
		_data->setObject( ox, oy, OBJECT_BLOCK );
	}
}
/*
void ObjectEditor::save( ) const {
	std::string filename = Application::getInstance( )->inputString( 0, 20 );
	if ( filename.size( ) == 0 ) {
		return;
	}
	_data->saveObject( DIRECTORY + filename );
}

void ObjectEditor::load( ) {
	std::string filename = Application::getInstance( )->inputString( 0, 20 );
	if ( filename.size( ) == 0 ) {
		return;
	}
	_data->loadObject( DIRECTORY + filename );
}
*/