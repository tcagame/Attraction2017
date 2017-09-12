#pragma once
#include "Task.h"
#include <string>

PTR( RockTheater );
PTR( Movie );
PTR( Image );

class RockTheater : public Task {
public:
	static std::string getTag( ) { return "ROCKTHEATER"; };
	static RockTheaterPtr getTask( );
public:
	RockTheater(  );
	virtual ~RockTheater( );
public:
	virtual void initialize( ) = 0;
	MoviePtr getMovie( ) const;
	ImagePtr getImage( ) const;
protected:
	void setMovie( MoviePtr movie );
	void setImage( ImagePtr image );
	void playMovie( );
	void stopMovie( );
private:
	MoviePtr _movie;
	ImagePtr _image;
};

