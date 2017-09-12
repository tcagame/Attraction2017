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
		COMMAND_AREA,
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
	bool excuteIp( ) const;
	bool excuteDevice( ) const;
	bool excuteContinue( std::vector< std::string > command );
	bool excuteToku( std::vector< std::string > command );
	bool excutePower( std::vector< std::string > command );
	bool excuteMoney( std::vector< std::string > command );
	bool excuteItem( std::vector< std::string > command );
	bool excuteArea( std::vector< std::string > command );
	std::vector< std::string > getSpritCommand( ) const;
private:
	std::string _command;
	StatusPtr _status;
};

