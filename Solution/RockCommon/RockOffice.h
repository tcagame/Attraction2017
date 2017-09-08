#pragma once
#include "Task.h"
#include <string>
#include <list>

PTR( RockOffice );
PTR( RockEventCharacter );

class RockOffice : public Task {
public:
	static std::string getTag( ) { return "ROCKOFFICE"; };
	static RockOfficePtr getTask( );
public:
	RockOffice( );
	virtual ~RockOffice( );
public:
	void update( );
	void clean( );
	void add( RockEventCharacterPtr chara );
	std::list< RockEventCharacterPtr > getEventCharacters( ) const;
private:
	std::list< RockEventCharacterPtr > _event_chara_list;
};

