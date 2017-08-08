#include "RockClientInfo.h"
#include "Application.h"

RockClientInfoPtr RockClientInfo::getTask( ) {
	return std::dynamic_pointer_cast< RockClientInfo >( Application::getInstance( )->getTask( getTag( ) ) );
}


RockClientInfo::RockClientInfo( unsigned int client_id ) :
_client_id( client_id ) {
}


RockClientInfo::~RockClientInfo( ) {
}

void RockClientInfo::update( ) {
}

unsigned int RockClientInfo::getClientId( ) const {
	return _client_id;
}
