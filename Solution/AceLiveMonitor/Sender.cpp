#include "Sender.h"
#include "Application.h"
#include "Server.h"
#include "SynchronousData.h"

SenderPtr Sender::getTask( ) {
	return std::dynamic_pointer_cast< Sender >( Application::getInstance( )->getTask( getTag( ) ) );
}



Sender::Sender( SynchronousDataPtr data ) :
_data( data ) {
}


Sender::~Sender( ) {
}

void Sender::update( ) {
	Server::getTask( )->sendUdp( _data );
}
