#pragma once
#include "Task.h"
#include <string>

PTR( Debug );

class Debug : public Task {
public:
	static std::string getTag( ) { return "DEBUG"; };
	static DebugPtr getTask( );
public:
	Debug( );
	virtual ~Debug( );
public:
	void update( );
	bool isDebug( ) const;
private:
	bool _debug;
};

