#pragma once
#include "RockMap.h"
#include "mathmatics.h"
#include <vector>

PTR( Movie );
PTR( Status );
PTR( Image );

class RockMapResult :	public RockMap {
public:
	RockMapResult( StatusPtr status );
	virtual ~RockMapResult( );
public:
	void initialize( );
	void update( );
private:
	enum ENDING {
		ENDING_HEAVEN,
		ENDING_HUMAN,
		ENDING_BRUET,
		ENDING_BRAD,
		ENDING_HELL,
	};
private:
	void drawEnding( int player, ENDING ending );
private:
	StatusPtr _status;
	std::vector< ImagePtr > _end_image;
};

