#pragma once
#include "Task.h"
#include <string>

PTR( Speaker );
PTR( Status );

class Speaker: public Task {
public:
	static std::string getTag( ) { return "SPEAKER"; };
	static SpeakerPtr getTask( );
public:
	Speaker( StatusPtr status );
	virtual ~Speaker( );
public:
	void update( );
private:
	StatusPtr _status;
	bool _normal_bgm;
};

