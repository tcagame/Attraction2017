#include "ObjectEditor.h"
#include "Mouse.h"
#include "ObjectCursor.h"
#include "Data.h"
#include "ace_define.h"
#include "Application.h"
#include "Keyboard.h"

const std::string DIRECTORY = "../Resource/Ace/MapData/";

ObjectEditor::ObjectEditor( DataPtr data, ObjectCursorConstPtr object_cursor ) :
_data( data ),
_object_cursor( object_cursor ),
_click_active( false ),
_object( OBJECT_NONE ) {
}

ObjectEditor::~ObjectEditor( ) {
}

void ObjectEditor::update( ) {
	MousePtr mouse( Mouse::getTask( ) );
	if ( mouse->isHoldLeftButton( ) &&
		_object_cursor->isOnChip( ) &&
		_click_active ) {
		int ox = _object_cursor->getGX( ) + _object_cursor->getScrollX( );
		int oy = _object_cursor->getGY( );
		_data->setObject( ox, oy, _object );
	}
	if ( !mouse->isHoldLeftButton( ) ) {
		_click_active = true;
	}
	editWidth( );
}

void ObjectEditor::setObject( unsigned char object ) {
	_object = object;
	_click_active = false;
}

unsigned char ObjectEditor::getObject( ) const {
	return _object;
}

void ObjectEditor::editWidth( ) {
	KeyboardPtr keyboard( Keyboard::getTask( ) );
	int mx = _object_cursor->getScrollX( ) + _object_cursor->getGX( );
	if ( keyboard->isPushKey( "+" ) ) {
		_data->insert( ( mx / PAGE_OBJECT_WIDTH_NUM ) % _data->getPageNum( ) );
	}
	if ( keyboard->isPushKey( "-" ) ) {
		_data->erase( (  mx / PAGE_OBJECT_WIDTH_NUM ) % _data->getPageNum( ) );
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