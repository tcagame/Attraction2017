#pragma once
#include "Task.h"
#include <string>
#include "status.h"

PTR( StatusReceiver );
PTR( Status );

class StatusReceiver : public Task {
public:
	static std::string getTag( ) { return "STATUSRECEIVER"; };
	static StatusReceiverPtr getTask( );
public:
	StatusReceiver( );
	virtual ~StatusReceiver( );
public:
	void update( );
private:
	StatusPtr _status;
};

