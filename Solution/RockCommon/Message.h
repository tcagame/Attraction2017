#pragma once

#include "Data.h"
#include "smart_ptr.h"

PTR( Message );

class Message : public Data {
public:
	enum COMMAND {
		COMMAND_TOKU,
		COMMAND_POWER,
		COMMAND_MONEY,
		COMMAND_ITEM,
		COMMAND_STATE,
		COMMAND_CONTINUE,
		MAX_COMMAND
	};
public:
	Message( ) { }
	virtual ~Message( ) { }
public:
	void * getPtr( ) {
		return ( void * )_dummy;
	}

	int getSize( ) {
		return sizeof( _dummy );
	}
private:
	int _dummy[ 100 ];
};