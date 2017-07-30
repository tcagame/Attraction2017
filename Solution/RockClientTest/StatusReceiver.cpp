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
}
