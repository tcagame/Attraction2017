#include "RockDebug.h"
#include "Application.h"
#include "Keyboard.h"

RockDebugPtr RockDebug::getTask( ) {
	return std::dynamic_pointer_cast< RockDebug >( Application::getInstance( )->getTask( getTag( ) ) );
}

RockDebug::RockDebug( ) :
_debug( false ) {
}

RockDebug::~RockDebug( ) {
}

void RockDebug::update( ) {
	if ( Keyboard::getTask( )->isPushKey( "SPACE" ) ) {
		_debug = !_debug;
	}
}

bool RockDebug::isDebug( ) const {
	return _debug;
}
