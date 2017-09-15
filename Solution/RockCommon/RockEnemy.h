#pragma once
#include "RockCharacter.h"
#include "define.h"

class RockEnemy:  public RockCharacter {
public:
	RockEnemy( const Vector& pos, DOLL id, int hp, int force = 1, int radius = 10, int height = 30, bool mass = true, bool head = true );
	virtual ~RockEnemy( );
public:
	int getForce( ) const;
	void damage( int force );
	bool isFinished( ) const;
	void reset( );
	ModelMV1Ptr getModel( ) const;
	virtual double getAnimTime( ) const = 0;
	virtual void dropItem( ) { };
	void kickDown( );
private:
	int _force;
	int _hp;
	int _max_hp;
	Vector _start_pos;
	bool _finished;
};

