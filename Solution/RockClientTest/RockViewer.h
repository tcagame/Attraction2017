#pragma once
#include "Task.h"
#include <string>

class RockViewer : public Task {
public:
	RockViewer( );
	virtual ~RockViewer( );
public:
	void update( );
private:
	void drawMap( ) const;
};

