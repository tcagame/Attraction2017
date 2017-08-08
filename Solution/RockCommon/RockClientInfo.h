#pragma once
#include "Task.h"
#include <string>

PTR( RockClientInfo );

class RockClientInfo : public Task {
public:
	static std::string getTag( ) { return "ROCKCLIENTINFO"; };
	static RockClientInfoPtr getTask( );
public:
	RockClientInfo( unsigned int client_id );
	virtual ~RockClientInfo( );
public:
	void update( );
	unsigned int getClientId( ) const;
public:
	unsigned int _client_id;
};

