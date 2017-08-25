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
		int id;
		double radius;
		bool attack;
		Vector pos;
		DIR dir;
		Target( ) :
			id ( 0 ),
			radius( 0.0 ),
			attack( false ),
			pos( Vector( ) ),
			dir( DIR_RIGHT ) {
		}
	};
public:
	Monmotaro( const PLAYER player, const Vector& pos, const Target& target );
	virtual ~Monmotaro( );
public:
	void setTarget( const Target& target );
	ACTION getAction( ) const;
private:
	void act( );
	void damage( int force );
	void setSynchronousData( );
private:
	PLAYER _player;
	ACTION _action;
	Target _target;
};

