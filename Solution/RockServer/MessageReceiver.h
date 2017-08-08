#pragma once
#include "Task.h"
#include <string>

PTR( MessageReceiver );
PTR( Status );

class MessageReceiver : public Task {
public:
	MessageReceiver( StatusPtr status );
	virtual ~MessageReceiver( );
public:
	void update( );
private:
	StatusPtr _status;
};

