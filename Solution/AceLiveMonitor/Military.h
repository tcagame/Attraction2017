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
	const std::list< EnemyPtr > getEnemyList( ) const;
	const std::list< EnemyPtr > getEventEnemyList( ) const;
	void popUp( EnemyPtr enemy );
	void popUpEventEnemy( EnemyPtr enemy );
	void createBoss( );
	EnemyPtr getBoss( ) const;
private:
	std::list< EnemyPtr > _enemies;
	std::list< EnemyPtr > _event_enemies;
	EnemyPtr _boss;
};

