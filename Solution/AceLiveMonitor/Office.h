#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include <string>
#include <list>
#include "ace_define.h"

PTR( Office );
PTR( NPC );

class Office : public Task {
public:
	static std::string getTag( ) { return "OFFICE"; };
	static OfficePtr getTask( );
public:
	Office( );
	virtual ~Office( );
public:
	void update( );
	void popUpNPC( EVENT type );
	std::list< NPCPtr > getNPC( ) const;
	void eraseEventNPC( );
	void addEventNPC( NPCPtr npc );
private:
	std::list< NPCPtr > _npc;
};

