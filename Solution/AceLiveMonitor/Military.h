#pragma once
#include "Task.h"
#include <string>
#include <list>

PTR( Military );
PTR( Enemy );
PTR( Character );

class Military : public Task {
public:
	static std::string getTag( ) { return "MILITARY"; };
	static MilitaryPtr getTask( );
public:
	Military( );
	virtual ~Military( );
public:
	void update( );
	EnemyPtr getOverLappedEnemy( CharacterConstPtr character ) const;
	const std::list< EnemyPtr > getList( ) const;
	void popUp( EnemyPtr enemy );
private:
	std::list< EnemyPtr > _enemies;
};

