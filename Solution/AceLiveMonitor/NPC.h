#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include "Character.h"
#include <string>
#include <list>

PTR( NPC );

class NPC : public Task {
public:
	static std::string getTag( ) { return "NPC"; };
	static NPCPtr getTask( );
public:
	NPC( );
	virtual ~NPC( );
public:
	void update( );
	void popUpNPC( );
	std::list< CharacterPtr > getNPCChara( ) const;
private:
	std::list< CharacterPtr > _npc_chara;
};

