#pragma once
#include <string>
#include <array>
#include "define.h"
#include "Task.h"

PTR( Log );

class Log : public Task {
public:
	static std::string getTag( ) { return "LOG"; };
	static LogPtr getTask( );
public:
	Log( );
	virtual ~Log( );
public:
	void update( );
	void addMessage( std::string message );
	std::string getMessage( int idx ) const;
private:
	std::array< std::string, MESSAGE_COUNT > _message;
};


