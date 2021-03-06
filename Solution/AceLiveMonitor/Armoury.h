#pragma once
#include "Task.h"
#include <string>
#include "smart_ptr.h"
#include <list>
#include <array>
#include "ViewerDebug.h"

PTR( Shot );
PTR( Armoury );
PTR( Impact );
PTR( ShotPlayer );
PTR( ShotMonmotaro );

class Armoury : public Task {
public:
	static std::string getTag( ) { return "ARMOURY"; };
	static ArmouryPtr getTask( );
public:
	Armoury( );
	virtual ~Armoury( );
public:
	void add( ShotPtr shot );
	void update( );
	ShotConstPtr getShot( int idx ) const;
	int getMaxShotNum( ) const;
	void pushDebugData( ViewerDebug::Data& data );
	void eraseEventShot( );
	void setSynchronousData( );
private:
	static const int MAX_SHOT_NUM = 100;
	int _shot_id;
	std::array< ShotPtr, MAX_SHOT_NUM > _shot_list;
};

