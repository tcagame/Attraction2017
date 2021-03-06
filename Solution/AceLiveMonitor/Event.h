#pragma once
#include "ace_define.h"

class Event {
public:
	enum FADE {
		FADE_IN,
		FADE_OUT,
	};
public:
	Event( EVENT type, DIR exit_dir );
	virtual ~Event( );
public:
	EVENT getType( ) const;
	virtual void update( ) = 0;
	virtual void join( PLAYER target ) = 0;
	void fade( );
	bool isFinished( );
	FADE getFade( ) const;
protected:
	void escape( );
	void exit( );
private:
	const EVENT _type;
	const DIR _exist_dir;
	FADE _fade_type;
	int _fade_count;
	bool _exiting;
};

