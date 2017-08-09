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
protected:
	void act( );
private:
	enum ACTION {
		ACTION_WAIT,
		ACTION_JUMP,
		ACTION_WALK,
		ACTION_BRAKE,
	};
private:
	void setAction( ACTION action );
	void actOnWaiting( );
	void actOnJumping( );
	void actOnWalking( );
	void actOnBraking( );
private:
	StatusPtr _status;
	ACTION _action;
	int _id;
};

