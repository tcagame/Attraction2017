#pragma once
#include "Task.h"
#include <string>
#include "mathmatics.h"

PTR( RockMapStreetCamera );

class RockMapStreetCamera : public Task {
public:
	static std::string getTag( ) { return "ROCKMAPSTREETCAMERA"; };
	static RockMapStreetCameraPtr getTask( );
public:
	RockMapStreetCamera( );
	virtual ~RockMapStreetCamera( );
public:
	void initialize( );
	void update( );
private:
	Vector _pos;
	Vector _target;
};

