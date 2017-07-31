#pragma once
#include "Task.h"
#include <string>
#include "mathmatics.h"

PTR( RockCamera );

class RockCamera : public Task {
public:
	static std::string getTag( ) { return "ROCKCAMERA"; };
	static RockCameraPtr getTask( );
public:
	RockCamera( );
	virtual ~RockCamera( );
public:
	void initialize( );
	void update( );
private:
	Vector _pos;
	Vector _target;
};

