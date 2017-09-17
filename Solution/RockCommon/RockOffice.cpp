#include "RockOffice.h"
#include "Application.h"
#include "RockEventCharacter.h"

RockOfficePtr RockOffice::getTask( ) {
	return std::dynamic_pointer_cast< RockOffice >( Application::getInstance( )->getTask( getTag( ) ) );
}

RockOffice::RockOffice( ) {
}


RockOffice::~RockOffice( ) {
}

void RockOffice::update( ) {
	std::list< RockEventCharacterPtr >::iterator ite = _event_chara_list.begin( );
	while ( ite != _event_chara_list.end( ) ) {
		RockEventCharacterPtr chara = *ite;
		if ( !chara ) {
			ite++;
			continue;
		}
		if ( chara->isFinished( ) ) {
			ite = _event_chara_list.erase( ite );
			continue;
		}

		chara->update( );
		ite++;
	}
}

void RockOffice::add( RockEventCharacterPtr chara ) {
	_event_chara_list.push_back( chara );
}

std::list< RockEventCharacterPtr > RockOffice::getEventCharacters( ) const {
	return _event_chara_list;
}

void RockOffice::clean( ) {
	_event_chara_list = { };
}