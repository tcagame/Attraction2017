#pragma once
#include "ace_define.h"

class Event {
public:
	enum FADE {
		FADE_IN,
		FADE_OUT,
	};
public:
	Event( EVENT type );
	virtual ~Event( );
public:
	EVENT getType( ) const;
	virtual void update( ) = 0;
	virtual bool isJoining( ) const = 0;
	virtual void join( PLAYER target ) = 0;
	bool isFinished( );
	void fade( );
	FADE getFade( ) const;
protected:
	void exit( );
private:
	EVENT _type;
	FADE _fade_type;
	int _fade_count;
	bool _exiting;
};

