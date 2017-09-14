#pragma once
#include "Task.h"
#include <string>
#include <list>

PTR( Military );
PTR( Enemy );
PTR( EnemyBoss );
PTR( Character );
PTR( Impact );

class Military : public Task {
public:
	static std::string getTag( ) { return "MILITARY"; };
	static MilitaryPtr getTask( );
public:
	Military( );
	virtual ~Military( );
public:
	void update( );
	EnemyPtr getOverlappedEnemy( CharacterConstPtr character ) const;
	const std::list< EnemyPtr > getEnemyList( ) const;
	const std::list< EnemyPtr > getEventEnemyList( ) const;
	void popUp( EnemyPtr enemy );
	void popUpEventEnemy( EnemyPtr enemy );
	void createEventEnemy( );
	void eraseEventEnemy( );
	EnemyPtr getBoss( ) const;
	EnemyPtr getHellFire( ) const;
private:
	void dropMoney( EnemyConstPtr enemy );
private:
	std::list< EnemyPtr > _enemies;
	std::list< EnemyPtr > _event_enemies;
	EnemyPtr _hell_fire;
	EnemyBossPtr _boss;
};

