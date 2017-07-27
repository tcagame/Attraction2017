#pragma once
#include <string>
#include <vector>
#include "smart_ptr.h"

PTR( Log );
PTR( StatusSender );

class Command {
public:
	enum COMMAND {
		COMMAND_IP,
		COMMAND_DEVICE,
		COMMAND_CONTINUE,
		COMMAND_TOKU,
		COMMAND_POWER,
		COMMAND_MONEY,
		COMMAND_ITEM,
		MAX_COMMAND
	};
public:
	Command( StatusSenderPtr status_sender );
	virtual ~Command( );
public:
	void update( );
	void draw( ) const;
	void drawFrame( ) const;
	void drawString( ) const;
private:
	void excute( );
	std::vector< std::string > getSpritCommand( ) const;
private:
	std::string _command;
	LogPtr _log;
	StatusSenderPtr _status_sender;
};

