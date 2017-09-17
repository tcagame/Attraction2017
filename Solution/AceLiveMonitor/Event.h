#pragma once
#include "ace_define.h"

class Event {
public:
	Event( EVENT type );
	virtual ~Event( );
public:
	EVENT getType( ) const;
	virtual void update( ) = 0;
	virtual bool isFinished( ) const = 0;
	virtual bool isJoining( ) const = 0;
	virtual void join( PLAYER target ) = 0;
	void exit( );
private:
	EVENT _type;
};

