#pragma once
#include "ace_define.h"

class Event {
public:
	Event( EVENT type );
	virtual ~Event( );
public:
	virtual void update( ) = 0;
	EVENT getType( ) const;
private:
	EVENT _type;
};

