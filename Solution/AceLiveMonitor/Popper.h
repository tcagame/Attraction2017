#pragma once

#include "Task.h"
#include <string>
#include "smart_ptr.h"
#include <vector>

PTR( Popper );
PTR( Pop );
PTR( Enemy );

class Popper : public Task {
public:
	static std::string getTag( ) { return "POPPER"; };
	static PopperPtr getTask( );
public:
	Popper( );
	virtual ~Popper( );
public:
	void initialize( );
	void update( );
	void add( EnemyPtr pop_enemy );
private:
	std::vector< PopPtr > _pops;
	std::vector< EnemyPtr > _stock_enemies;
};

