#pragma once
#include "Task.h"
#include <string>
#include <list>

PTR( Military );
PTR( Enemy );

class Military : public Task {
public:
	static std::string getTag( ) { return "MILITARY"; };
	static MilitaryPtr getTask( );
public:
	Military( );
	virtual ~Military( );
public:
	void update( );
	const std::list< EnemyPtr > getList( ) const;
private:
	std::list< EnemyPtr > _enemies;
};

