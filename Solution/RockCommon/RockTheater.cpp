#include "RockTheater.h"
#include "Application.h"
#include "Movie.h"

RockTheaterPtr RockTheater::getTask( ) {
	return std::dynamic_pointer_cast< RockTheater >( Application::getInstance( )->getTask( getTag( ) ) );
}

RockTheater::RockTheater( ) {
}

RockTheater::~RockTheater( ) {
}

void RockTheater::playMovie( ) {
	if ( !_movie ) {
		return;
	}
	_movie->play( );
}

void RockTheater::stopMovie( ) {
	if ( !_movie ) {
		return;
	}
	_movie->stop( );
}

void RockTheater::setMovie( MoviePtr movie ) {
	_movie = movie;
}

MoviePtr RockTheater::getMovie( ) const {
	return _movie;
}