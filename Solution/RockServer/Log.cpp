#include "Log.h"
#include "Drawer.h"
#include "Application.h"


LogPtr Log::getTask( ) {
	return std::dynamic_pointer_cast< Log >( Application::getInstance( )->getTask( getTag( ) ) );
}


Log::Log( ) {
	_message = { };
}

Log::~Log( ) {
}

void Log::update( ) {
}

void Log::addMessage( std::string message ) {
	for ( int i = 0; i < MESSAGE_COUNT - 1; i++ ) {
		_message[ MESSAGE_COUNT - i - 1 ] = _message[ MESSAGE_COUNT - i - 2 ];
	}
	_message[ 0 ] = message;
}


std::string Log::getMessage( int idx ) const {
	return _message[ idx ];
}
