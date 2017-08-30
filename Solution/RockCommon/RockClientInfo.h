#pragma once
#include "Task.h"
#include <string>
#include <vector>

PTR( RockClientInfo );

class RockClientInfo : public Task {
public:
	static std::string getTag( ) { return "ROCKCLIENTINFO"; };
	static RockClientInfoPtr getTask( );
public:
	RockClientInfo( std::vector< unsigned int > client_id );
	virtual ~RockClientInfo( );
public:
	void update( );
	bool isActiveState( unsigned int player_state ) const;
public:
	std::vector< unsigned int > _client_id;
};

