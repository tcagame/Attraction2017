#pragma once
#include "mathmatics.h"

class Player {
public:
	enum ACTION {
		ACTION_WAIT,
		ACTION_WALK,
		ACTION_BRAKE,
		ACTION_FLOAT,
		ACTION_ATTACK,
	};
	enum DIR {
		DIR_LEFT,
		DIR_RIGHT,
	};
public:
	Player( int player_id, Vector pos );
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
	void actOnAttack( );
	void checkDir( );
private:
	int _act_count;
	Vector _pos;
	Vector _vec;
	ACTION _action;
	bool _standing;
	int _id;
	DIR _dir;
};

