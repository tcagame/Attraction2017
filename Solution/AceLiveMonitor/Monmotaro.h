#pragma once
#include "Character.h"

class Monmotaro : public Character {
public:
	enum ACTION {
		ACTION_HIDE,
		ACTION_ENTRY,
		ACTION_FADE_IN,
		ACTION_MOVE,
		ACTION_ATTACK,
		ACTION_FADE_OUT,
	};
public:
	Monmotaro( const Vector& pos );
	virtual ~Monmotaro( );
public:
	ACTION getAction( ) const;
private:
	void act( );
	void actOnHide( );
	void actOnEntry( );
	void actOnFadeIn( );
	void actOnMove( );
	void actOnFadeOut( );
	void setAction( ACTION action );
	void damage( int force );
	void setSynchronousData( );
private:
	int _tracking;
	ACTION _action;
};

