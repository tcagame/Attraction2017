#pragma once
#include "RockEnemyAttack.h"

class RockEnemyBossRockAttack : public RockEnemyAttack {
public:
	RockEnemyBossRockAttack( const Vector& pos, DOLL id, const Vector& dir );
	virtual ~RockEnemyBossRockAttack( );
public:
	double getAnimTime( ) const;
protected:
	void act( );
private:
	bool _jump;
	bool _back;
	Vector _dir;
	Vector _start_pos;
};

