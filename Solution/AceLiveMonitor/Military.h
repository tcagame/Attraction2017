#pragma once
#include "Task.h"
#include <string>
#include <list>
#include "ace_define.h"
#include "ViewerDebug.h"

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
	void initialize( );
	void update( );
	EnemyPtr getOverlappedEnemy( CharacterConstPtr character ) const;
	const std::list< EnemyPtr > getEnemyList( ) const;
	void popUp( EnemyPtr enemy );
	void pushDebugData( ViewerDebug::Data& data ) const;
	void eraseEventEnemy( );
	void shiftPos( int map_width );
	void setSynchronousData( ) const;
private:
	void updateEnemy( );
	void dropMoney( EnemyConstPtr enemy );
private:
	std::list< EnemyPtr > _enemies;
};

