#pragma once
#include "Character.h"

class Monmotaro : public Character {
public:
	Monmotaro( const Vector& pos, const Vector& target );
	virtual ~Monmotaro( );
public:
	enum ACTION {
		ACTION_FADE_IN,
		ACTION_MOVE_IN,
		ACTION_WAIT,
		ACTION_ATTACK,
		ACTION_OUT,
	};
public:
	void setTarget( const Vector& target );
	ACTION getAction( ) const;
private:
	void act( );
	void damage( int force );
	void setSynchronousData( );
private:
	ACTION _action;
	Vector _target;
};

