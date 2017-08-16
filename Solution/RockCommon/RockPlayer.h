#pragma once
#include "RockCharacter.h"
#include "smart_ptr.h"

PTR( Status );

class RockPlayer : public RockCharacter {
public:
	RockPlayer( StatusPtr status, const Vector& pos, int id );
	virtual ~RockPlayer( );
public:
	double getAnimTime( ) const;
	bool isActive( ) const;
	void bound( );
	void damage( int force );
	void back( );
	bool isDead( ) const;
protected:
	void act( );
private:
	enum ACTION {
		ACTION_WAIT,
		ACTION_JUMP,
		ACTION_WALK,
		ACTION_BRAKE,
		ACTION_DEAD,
	};
private:
	void setAction( ACTION action );
	void actOnWaiting( );
	void actOnJumping( );
	void actOnWalking( );
	void actOnBraking( );
	void actOnDead( );
private:
	StatusPtr _status;
	ACTION _action;
	int _id;
};

