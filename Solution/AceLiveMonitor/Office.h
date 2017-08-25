#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include <string>
#include <list>

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
	void popUpNPC( );
	std::list< NPCPtr > getNPC( ) const;
private:
	std::list< NPCPtr > _npc;
};

