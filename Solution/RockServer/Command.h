#pragma once
#include <string>
#include <vector>
#include "smart_ptr.h"

PTR( Log );

class Command {
public:
	enum COMMAND {
		COMMAND_TEST,
		COMMAND_IP,
		MAX_COMMAND
	};
public:
	Command( );
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
};

