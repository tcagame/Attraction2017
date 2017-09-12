#include "RockClientInfo.h"
#include "Application.h"

RockClientInfoPtr RockClientInfo::getTask( ) {
	return std::dynamic_pointer_cast< RockClientInfo >( Application::getInstance( )->getTask( getTag( ) ) );
}


RockClientInfo::RockClientInfo( std::vector< unsigned char > client_id ) :
_client_id( client_id ) {
}


RockClientInfo::~RockClientInfo( ) {
}

void RockClientInfo::update( ) {
}

bool RockClientInfo::isActiveState( unsigned char player_state ) const {
	bool result = false;
	int size = ( int )_client_id.size( );
	for ( int i = 0; i < size; i++ ) {
		if ( player_state == _client_id[ i ] ) {
			result = true;
			break;
		}
	}
	return result;
}
