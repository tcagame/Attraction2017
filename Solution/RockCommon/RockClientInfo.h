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
	RockClientInfo( std::vector< unsigned char > client_id );
	virtual ~RockClientInfo( );
public:
	void update( );
	bool isActiveState( unsigned char player_state ) const;
public:
	std::vector< unsigned char > _client_id;
};

