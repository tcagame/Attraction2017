#pragma once
#include "Character.h"

class Monmotaro : public Character {
public:
	enum ACTION {
		ACTION_ENTRY,
		ACTION_FADE_IN,
		ACTION_MOVE,
		ACTION_ATTACK,
		ACTION_FADE_OUT,
	};
	struct Target {
		Vector pos;
		DIR dir;
	};
public:
	Monmotaro( const Vector& pos, const Target& target );
	virtual ~Monmotaro( );
public:
	void setTarget( const Target& target );
	ACTION getAction( ) const;
private:
	void act( );
	void damage( int force );
	void setSynchronousData( );
private:
	ACTION _action;
	Target _target;
};

