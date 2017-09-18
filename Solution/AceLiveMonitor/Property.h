#pragma once
#include "Task.h"
#include <string>
#include <map>

PTR( Property );

class Property : public Task {
public:
	static std::string getTag( ) { return "PROPERTY"; };
	static PropertyPtr getTask( );
public:
	Property( );
	virtual ~Property( );
public:
	void initialize( );
	void update( );
	int getData( std::string tag );
private:
	std::map< std::string, int > _data;
};

