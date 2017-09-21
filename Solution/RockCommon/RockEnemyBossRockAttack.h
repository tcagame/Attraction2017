#pragma once
#include "RockEnemyAttack.h"

class RockEnemyBossRockAttack : public RockEnemyAttack {
public:
	RockEnemyBossRockAttack( const Vector& pos, DOLL id, const Vector& dir );
	virtual ~RockEnemyBossRockAttack( );
public:
	double getAnimTime( ) const;
	void setPos( const Vector& pos );
	void damage( int force );
protected:
	void act( );
private:
	void assaultPlayer( );
private:
	Vector _dir;
	Vector _start_pos;
};

