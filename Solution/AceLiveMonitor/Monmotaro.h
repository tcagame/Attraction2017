#pragma once
#include "Character.h"

PTR( Monmotaro );
PTR( Player );

class Monmotaro : public Character {
public:
	enum ACTION {
		ACTION_HIDE,
		ACTION_APPEAR,
		ACTION_FADEIN,
		ACTION_MOVE,
		ACTION_ATTACK,
		ACTION_FADEOUT,
	};
public:
	Monmotaro( );
	virtual ~Monmotaro( );
public:
	void appear( PlayerPtr player );
	void setSynchronousData( );
private:
	void act( );
	void actOnHide( );
	void actOnAppear( );
	void actOnFadeIn( );
	void actOnMove( );
	void actOnFadeOut( );
	void setAction( ACTION action );
private:
	PlayerConstPtr _player;
	int _capture_power;
	ACTION _action;
};

