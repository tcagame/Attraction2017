#pragma once
#include "Task.h"
#include "Message.h"
#include <string>

PTR( MessageSender );

class MessageSender : public Task {
public:
	static std::string getTag( ) { return "MESSAGESENDER"; };
	static MessageSenderPtr getTask( );
public:
	MessageSender( MessagePtr message );
	virtual ~MessageSender( );
public:
	void update( );
	void sendMessage( int player_id, Message::COMMAND command, void* value );
private:
	MessagePtr _message;
};

