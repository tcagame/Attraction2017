#pragma once
#include "RockTheater.h"
#include <vector>
#include "mathmatics.h"

PTR( Status );
PTR( ImageTarget );

class RockTheaterResult : public RockTheater {
public:
	RockTheaterResult( StatusPtr status );
	virtual ~RockTheaterResult( );
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
	void createImage( );
	void createEndingImage( );
	void updateEnding( );
	void exitClient( int player );
	bool isShown( const Vector& pos );
private:
	bool _play;
	std::vector< ImagePtr > _images;
	ImageTargetPtr _draw_image;
	StatusPtr _status;
	int _ending_index;
	int _ending_time;
	int _offset_y;
	int _ending_vy;
	bool _shown;
	std::vector< ImagePtr > _end_image;
};

