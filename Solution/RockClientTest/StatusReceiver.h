#pragma once
#include "Task.h"
#include <string>
#include "status.h"

PTR( StatusReceiver );

class StatusReceiver : public Task {
public:
	static std::string getTag( ) { return "STATUSRECEIVER"; };
	static StatusReceiverPtr getTask( );
public:
	StatusReceiver( );
	virtual ~StatusReceiver( );
public:
	void update( );
	ROCK_DATA getData( ) const;
private:
	ROCK_DATA _data;
};

