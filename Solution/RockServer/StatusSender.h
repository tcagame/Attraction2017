#pragma once
#include "status.h"
#include "define.h"
#include <array>

class StatusSender {
public:
	StatusSender( );
	virtual ~StatusSender( );
public:
	void update( );
	ROCK_DATA getData( ) const;
	bool setContinueNum( int idx, int num );
private:
	ROCK_DATA _data;
	std::array< int, ROCK_PLAYER_NUM > _reset_count;//�{�^���̃J�E���g
};