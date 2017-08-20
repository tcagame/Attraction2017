#pragma once
#include "Task.h"
#include <string>

PTR( Sender );
PTR( SynchronousData );

class Sender : public Task {
public:
	static std::string getTag( ) { return "SENDER"; };
	static SenderPtr getTask( );
public:
	Sender( SynchronousDataPtr data );
	virtual ~Sender ( );
public:
	void update( );
private:
	SynchronousDataPtr _data;
};

