#pragma once
#include "Task.h"
#include <string>

PTR( Game );
PTR( Viewer );
PTR( Family );
PTR( Armoury );

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
};

