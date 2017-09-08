#pragma once
#include "Task.h"
#include <string>
#include <vector>

PTR( MessageReceiver );
PTR( Status );
PTR( Message );

class MessageReceiver : public Task {
public:
	static std::string getTag( ) { return "MESSAGERACIEVER"; };
	static MessageReceiverPtr getTask( );
public:
	MessageReceiver( StatusPtr status, MessagePtr message );
	virtual ~MessageReceiver( );
public:
	void update( );
private:
	std::vector< std::string > getSprit( std::string command ) const;
	void excute( std::vector< std::string > command );
	void excuteToku( std::vector< std::string > command );
	void excutePower( std::vector< std::string > command );
	void excuteMoney( std::vector< std::string > command );
	void excuteItem( std::vector< std::string > command );
	void excuteState( std::vector< std::string > command );
	void excuteContinue( std::vector< std::string > command );
	void updateFamily( );
private:
	StatusPtr _status;
	MessagePtr _message;
};