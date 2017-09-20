#pragma once
#include "RockCharacter.h"

class RockAncestors : public RockCharacter {
public:
	RockAncestors( int id );
	virtual ~RockAncestors( );
public:
	void pop( );
	void fadeOut( );
	bool isActive( );
	ModelMV1Ptr getModel( ) const;
	void resetPos( );
protected:
	void act( );
private:
	enum ACTION {
		ACTION_ABSENT,
		ACTION_FADEIN,
		ACTION_FADEOUT,
		ACTION_FOLLOW,
	};
private:
	void actOnAbsent( );
	void actOnFadeIn( );
	void actOnFadeOut( );
	void actOnFollow( );
private:
	int _player_id;
	int _fadein_effect;
	ACTION _action;
};

