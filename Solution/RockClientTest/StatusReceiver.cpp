#include "StatusReceiver.h"
#include "Application.h"
#include "Client.h"

StatusReceiverPtr StatusReceiver::getTask( ) {
	return std::dynamic_pointer_cast< StatusReceiver >( Application::getInstance( )->getTask( getTag( ) ) );
}

StatusReceiver::StatusReceiver( ) {
}

StatusReceiver::~StatusReceiver( ) {
}

void StatusReceiver::update( ) {
	Client::getTask( )->recieveClientData( ( void* )&_data, sizeof( ROCK_DATA ) );
}

ROCK_DATA StatusReceiver::getData( ) const {
	return _data;
}
