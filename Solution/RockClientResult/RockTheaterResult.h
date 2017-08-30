#pragma once
#include "RockTheater.h"

class RockTheaterResult : public RockTheater {
public:
	RockTheaterResult( );
	virtual ~RockTheaterResult( );
public:
	void initialize( );
	void update( );
private:
	bool _play;
};

