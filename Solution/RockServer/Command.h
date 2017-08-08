#pragma once
#include <string>
#include <vector>
#include "smart_ptr.h"
#include "Task.h"

PTR( Command );
PTR( Status );

class Command : public Task {
public:
	static std::string getTag( ) { return "COMMAND"; };
	static CommandPtr getTask( );
public:
	enum COMMAND {
		COMMAND_IP,
		COMMAND_DEVICE,
		COMMAND_CONTINUE,
		COMMAND_TOKU,
		COMMAND_POWER,
		COMMAND_MONEY,
		COMMAND_ITEM,
		COMMAND_STATE,
		MAX_COMMAND
	};
public:
	Command( StatusPtr status );
	virtual ~Command( );
public:
	void update( );
	std::string getCommand( ) const;
private:
	void excute( );
	std::vector< std::string > getSpritCommand( ) const;
	unsigned int getState( std::string str );
private:
	std::string _command;
	StatusPtr _status;
};

