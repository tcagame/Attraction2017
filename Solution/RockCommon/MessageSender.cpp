#include "MessageSender.h"
#include "Application.h"
#include "Client.h"

MessageSenderPtr MessageSender::getTask( ) {
	return std::dynamic_pointer_cast< MessageSender >( Application::getInstance( )->getTask( getTag( ) ) );
}


MessageSender::MessageSender( MessagePtr message ) :
_message( message ) {
}


MessageSender::~MessageSender( ) {
}


void MessageSender::update( ) {
}


void MessageSender::sendMessage( int player_id, Message::COMMAND command, void* value ) {
	std::string message = "";
	switch ( command ) {
	case Message::COMMAND_TOKU:
		message = "toku " + std::to_string( player_id ) + " " + std::to_string( *( int* )value ); 
		break;
	case Message::COMMAND_MONEY:
		message = "money " + std::to_string( player_id ) + " " + std::to_string( *( int* )value ); 
		break;
	case Message::COMMAND_POWER:
		message = "power " + std::to_string( player_id ) + " " + std::to_string( *( int* )value ); 
		break;
	case Message::COMMAND_ITEM:
		message = "item " + std::to_string( player_id ) + " "; 
		for ( int i = 0; i < 8; i++ ) {
			int check = 1 >> ( 7 - i );
			if ( check & *( unsigned char* )value ) {
				message += "1";
			} else {
				message += "0";
			}
		}
		break;
	case Message::COMMAND_STATE:
		message = "state " + std::to_string( player_id ) + " "; 
		for ( int i = 0; i < 16; i++ ) {
			unsigned int check = 1 << ( 15 - i );
			if ( check & *( unsigned int* )value ) {
				message += "1";
			} else {
				message += "0";
			}
		}
		break;
	}

	char* str = ( char* )_message->getPtr( );
	memcpy_s( _message->getPtr( ), _message->getSize( ), message.c_str( ), message.size( ) + 1 );
	Client::getTask( )->sendTcp( _message );
}
