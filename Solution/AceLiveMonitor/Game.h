#pragma once
#include "Task.h"
#include <string>

PTR( Game );
PTR( Viewer );
PTR( Family );
PTR( PsychicManager );

class Game : public Task {
public:
	static std::string getTag( ) { return "GAME"; };
	static GamePtr getTask( );
public:
	Game( );
	virtual ~Game( );
public:
	void initialize( );
	void update( );
	PsychicManagerPtr getPsychicManager( );
private:
	PsychicManagerPtr _psychic_manager;
	ViewerPtr _viewer;
	FamilyPtr _family;
};

