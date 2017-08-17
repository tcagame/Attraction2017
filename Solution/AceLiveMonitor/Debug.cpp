#include "Debug.h"
#include "Application.h"
#include "Keyboard.h"

DebugPtr Debug::getTask( ) {
	return std::dynamic_pointer_cast< Debug >( Application::getInstance( )->getTask( getTag( ) ) );
}


Debug::Debug( ) :
_debug( false ) {
}


Debug::~Debug( ) {
}

void Debug::update( ) {
	KeyboardPtr keyboard = Keyboard::getTask( );
	if ( keyboard->isPushKey( "SPACE" ) ) {
		_debug = !_debug;
	}
}

bool Debug::isDebug( ) const {
	return _debug;
}