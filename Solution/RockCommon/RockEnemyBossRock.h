#pragma once
#include "RockEnemyBoss.h"
#include <array>

PTR( RockEnemyBossRockAttack );

class RockEnemyBossRock : public RockEnemyBoss {
public:
	RockEnemyBossRock( const Vector& pos );
	virtual ~RockEnemyBossRock( );
public:
	double getAnimTime( ) const;
	void dropItem( );
protected:
	void act( );
	void stopEffect( );
private:
	int _soul_handle;
	static const int STONE_NUM = 9;
	std::array< RockEnemyBossRockAttackPtr, STONE_NUM > _stones;
};

