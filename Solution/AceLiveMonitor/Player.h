#pragma once
#include "mathmatics.h"

class Player {
public:
	enum ACTION {
		ACTION_WAIT,
		ACTION_WALK,
		ACTION_BRAKE,
		ACTION_FLOAT,
	};
	enum DIR {
		DIR_LEFT,
		DIR_RIGHT,
	};
public:
	Player( Vector pos );
	virtual ~Player( );
public:
	void update( );
	Vector getPos( ) const;
	ACTION getAction( ) const;
	int getActCount( ) const;
	DIR getDir( ) const;
private:
	void actOnWaiting( );
	void actOnWalking( );
	void actOnBreaking( );
	void actOnFloating( );
	void checkDir( );
private:
	int _act_count;
	Vector _pos;
	Vector _vec;
	ACTION _action;
	bool _standing;
	DIR _dir;
};

