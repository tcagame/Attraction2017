#pragma once
#include "Task.h"
#include <string>

PTR( Military );

class Military : public Task {
public:
	static std::string getTag( ) { return "MILITARY"; };
	static MilitaryPtr getTask( );
public:
	Military( );
	virtual ~Military( );
};

