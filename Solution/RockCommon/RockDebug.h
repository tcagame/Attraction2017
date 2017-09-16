#pragma once
#include "Task.h"
#include <string>

PTR( RockDebug );

class RockDebug : public Task {
public:
	static std::string getTag( ) { return "ROCKDEBUG"; };
	static RockDebugPtr getTask( );
public:
	RockDebug( );
	virtual ~RockDebug( );
public:
	void update( );
	bool isDebug( ) const;
private:
	bool _debug;
};

