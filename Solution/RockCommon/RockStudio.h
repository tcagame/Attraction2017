#pragma once
#include "Task.h"
#include <string>
#include <array>
#include "define.h"

PTR( RockStudio );

class RockStudio : public Task {
public:
	static std::string getTag( ) { return "ROCKSTUDIO"; };
	static RockStudioPtr getTask( );
public:
	RockStudio( );
	virtual ~RockStudio( );
public:
	void initialize( );
	void update( );
	int getEffectHandle( int id );
private:
	std::array< int, MAX_EFFECT > _effect;
};